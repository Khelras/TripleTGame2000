#include "cCamera.h"

cCamera::cCamera(sf::Vector2f _position, sf::Vector2f _dimensions)
{
	m_Position = _position;

	m_CameraView = new sf::View(_position, sf::Vector2f(_dimensions));

	m_CameraView->setSize(_dimensions);
}

cCamera::~cCamera()
{
}

void cCamera::SetCenter(sf::Vector2f _camerapos)
{
	m_CameraView->setCenter(_camerapos);
}

void cCamera::Move(sf::Vector2f _offset)
{
	m_Position += _offset;
	m_CameraView->move(_offset);
}
