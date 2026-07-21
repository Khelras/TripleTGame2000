#pragma once
#include "SFML/Graphics.hpp"

class cCamera
{
public:
	sf::Vector2f m_Position;
	sf::View* m_CameraView;

	cCamera(sf::Vector2f _position, sf::Vector2f _dimensions);
	~cCamera();

	// Purpose: Sets the cameras center position
	void SetCenter(sf::Vector2f _camerapos);

	// Purpose: Moves the camera by the specified offset
	void Move(sf::Vector2f _offset);
};

