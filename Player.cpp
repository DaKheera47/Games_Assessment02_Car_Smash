#include <TL-Engine.h>
#include <iostream>
using namespace tle;

//#include "helpers.h";
#include "Player.h";
#include "dev.h";

Player::Player(IModel* model, float health, float currentSpeed, float maxSpeed, float acceleration, float deceleration)
{
	// constructor
	m_model = model;
	m_health = health;
	m_maxSpeed = maxSpeed;
	m_acceleration = acceleration;
	m_deceleration = deceleration;
	m_currentSpeed = currentSpeed;
	m_rotationSpeed = 5.0f;

	m_bbox.minX = -0.946118f;
	m_bbox.maxX = 0.946118f;

	m_bbox.minY = 0.0065695f;
	m_bbox.maxY = 1.50131f;

	m_bbox.maxZ = 1.97237f;
	m_bbox.minZ = -1.97237f;

	float centerX = (m_bbox.minX + m_bbox.maxX) / 2;
	float centerZ = (m_bbox.minZ + m_bbox.maxZ) / 2;

	m_radius = sqrt(pow(centerX - m_bbox.maxX, 2) + pow(centerZ - m_bbox.maxZ, 2));
}

Player::~Player()
{
	// destructor
}

void Player::HandleMovement(I3DEngine* myEngine, float deltaTime)
{
	m_prevPosition = { m_model->GetX(), m_model->GetY(), m_model->GetZ() };

	// pressing w increases speed my acceleration, until max speed is reached
	if (myEngine->KeyHeld(Key_W))
	{
		// going backward, pressing forward is twice the acceleration
		if (m_currentSpeed < m_maxSpeed && m_currentSpeed < 0)
		{
			m_currentSpeed += m_acceleration * 2 * deltaTime;
		}
		else if (m_currentSpeed < m_maxSpeed && m_currentSpeed >= 0)
		{
			m_currentSpeed += m_acceleration * deltaTime;
		}
	}

	// pressing s decreases speed by deceleration, until 0 is reached
	if (myEngine->KeyHeld(Key_S))
	{
		// going forward, pressing reverse is twice the deceleration
		if (m_currentSpeed > -m_maxSpeed && m_currentSpeed > 0)
		{
			m_currentSpeed -= m_acceleration * 2 * deltaTime;
		}
		else if (m_currentSpeed > -m_maxSpeed && m_currentSpeed <= 0)
		{
			m_currentSpeed -= m_acceleration * deltaTime;
		}
	}

	if (!myEngine->KeyHeld(Key_W) && !myEngine->KeyHeld(Key_S)) {
		if (round(m_currentSpeed) == 0)
		{
			m_currentSpeed = 0;
		}
		else if (m_currentSpeed > 0)
		{
			m_currentSpeed -= m_deceleration * deltaTime;
		}
		else if (m_currentSpeed < 0)
		{
			m_currentSpeed += m_deceleration * deltaTime;
		}
	}

	// don't rotate, or move if speed is 0
	if (m_currentSpeed == 0) return;

	m_model->MoveLocalZ(m_currentSpeed * deltaTime);

	// pressing a rotates the model left
	if (myEngine->KeyHeld(Key_A))
	{
		m_model->RotateY(-m_rotationSpeed * m_currentSpeed * deltaTime);
		//if (m_currentSpeed < 0)
		//{
		//	m_model->RotateY(m_rotationSpeed * m_currentSpeed * deltaTime);
		//}
		//else {
		//	m_model->RotateY(-m_rotationSpeed * m_currentSpeed * deltaTime);
		//}
	}

	// pressing d rotates the model right
	if (myEngine->KeyHeld(Key_D))
	{
		m_model->RotateY(m_rotationSpeed * m_currentSpeed * deltaTime);
		//if (m_currentSpeed < 0)
		//{
		//	m_model->RotateY(-m_rotationSpeed * m_currentSpeed * deltaTime);
		//}
		//else {
		//	m_model->RotateY(m_rotationSpeed * m_currentSpeed * deltaTime);
		//}
	}
}

SVector3 Player::GetPostion()
{
	SVector3 position;
	position.x = m_model->GetX();
	position.y = m_model->GetY();
	position.z = m_model->GetZ();
	return position;
}

void Player::SetPosition(SVector3 position)
{
	m_model->SetPosition(position.x, position.y, position.z);
}

void Player::SetSpeed(float speed)
{
	m_currentSpeed = speed;
}

void Player::UndoLastMovement()
{
	m_model->SetPosition(m_prevPosition.x, m_prevPosition.y, m_prevPosition.z);
}

IModel* Player::GetModel()
{
	return m_model;
}

float Player::GetRadius()
{
	return m_radius;
}
