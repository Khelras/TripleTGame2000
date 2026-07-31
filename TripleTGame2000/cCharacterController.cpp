#include "cCharacterController.h"
#include "cSpriteRenderer.h"

cCharacterController::cCharacterController(b2World& _world, const sf::Vector2f& _startPos, EPlayer _player, EGravityDirection _movementAxis, std::shared_ptr<sf::Texture> _Texture)
{
	// -- Initialize member variables -- //
	m_player = _player;
	m_movementAxis = _movementAxis;
	m_spriteRenderer.InitializeSprite(_Texture, 32, 32); // Assuming a 32x32 sprite size, can change later 
	CreatePhysicsBody(_world, _startPos);

	m_world = &_world;
	// -- //
}

cCharacterController::~cCharacterController()
{
	// Destroy the Box2D body when the character controller is destroyed
	if (m_world != nullptr && m_body != nullptr)
	{
		m_world->DestroyBody(m_body);
		m_body = nullptr;
	}
}

void cCharacterController::Update(float _deltaTime, const sf::Vector2f& _Input)
{
	//singleton pattern to get the instance of the input handler
	CInputHandler* inputHandler = CInputHandler::getInstance();

	//Apply both movement and gravity to the character
	ApplyMovement(_Input);
	ApplyCustomGravity();

	//check if the inputs are pressed for the player and flip the gravity direction
	if (inputHandler->ActionPressed(m_player))
	{
		FlipGravityDirection();
	}

}

void cCharacterController::DrawCharacters(sf::RenderWindow& _window)
{
	_window.draw(*m_spriteRenderer.GetSprite());
}

void cCharacterController::FlipGravityDirection()
{
	m_GravityDirection *= -1.0f; // Flip the gravity direction by multiplying by -1

	b2Vec2 velocity = m_body->GetLinearVelocity();

	if (m_movementAxis == EGravityDirection::Horizontal)
	{
		// If the movement axis is horizontal, we want to preserve the vertical velocity
		velocity.y = 0.0f; // Reset vertical velocity to zero
	}
	else
	{
		// If the movement axis is vertical, we want to preserve the horizontal velocity
		velocity.x = 0.0f; // Reset horizontal velocity to zero
	}

	//apply the modified velocity to the body
	m_body->SetLinearVelocity(velocity);
}

void cCharacterController::CreatePhysicsBody(b2World& _world, const sf::Vector2f& _startPos)
{
	// Create a Box2D body definition for the character
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	// Set the initial position of the body in Box2D world coordinates (meters)
	bodyDef.position.Set(_startPos.x / PixelsPerMeter, _startPos.y / PixelsPerMeter);

	bodyDef.fixedRotation = true; // Prevent rotation for a character
	bodyDef.allowSleep = false; // Prevent the body from sleeping to ensure it always responds to input
	m_body = _world.CreateBody(&bodyDef); //This creates the body in the Box2D world

	//Set the shape of the character (a box in this case can also be cahnged later :D)
	b2PolygonShape boxShape;
	boxShape.SetAsBox(14.0f / PixelsPerMeter, 14.0f / PixelsPerMeter); 


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;

	// Set the physical properties of the character
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f; // No bounce
	m_body->CreateFixture(&fixtureDef); //This creates the fixture for the body


}

void cCharacterController::ApplyMovement(const sf::Vector2f& _Input)
{
	if (m_body == nullptr)
	{
		return; // If the body is not created, exit the function
	}

	m_body->SetAwake(true); // Ensure the body is awake to respond to movement

	//get velocity of the body
	b2Vec2 velocity = m_body->GetLinearVelocity();

	// Apply movement based on the input vector and movement axis for rock preverse vertical velocity and for air preserver horizontal velocity
	if (m_movementAxis == EGravityDirection::Horizontal)
	{
		velocity.x = _Input.x * m_movementSpeed;
	}
	else //if its not horizontal then it must be vertical so we can just use else
	{
		velocity.y = -_Input.y * m_movementSpeed;
	}
	// Set the new velocity to the body
	m_body->SetLinearVelocity(velocity);
}

void cCharacterController::ApplyCustomGravity()
{
	//first we get mass to apply gravity force to the body f = ma where a = gravity 
	float mass = m_body->GetMass();
	b2Vec2 gravityForce(0.0f, 0.0f); //init to zero as we need to set it based on the gravity direction and axis

	if (m_movementAxis == EGravityDirection::Horizontal)
	{
		//Rock moves horizontally and falls vertically so we need to apply gravity in the y dir
		gravityForce.y = m_GravityDirection * m_gravityStrength * mass;
	}
	else
	{
		//air will be moving vertically and falls horizontally so we need to apply gravity force in the x direction
		gravityForce.x = -m_GravityDirection * m_gravityStrength * mass;
	}

	//Actually apply the gravity force to the body
	m_body->ApplyForceToCenter(gravityForce, true);
}

void cCharacterController::UpdateSprite()
{
	// Update the sprite position based on the Box2D body position
	b2Vec2 bodyPosition = m_body->GetPosition();
	m_spriteRenderer.GetSprite()->setPosition(sf::Vector2f(bodyPosition.x * PixelsPerMeter, bodyPosition.y * PixelsPerMeter));
	
}

void cCharacterController::UpdateVisuals(float _deltaTime)
{
	//Update the sprite position and rotation based on the physics body
	UpdateSprite();
	m_spriteRenderer.UpdateSprite(_deltaTime);
}
