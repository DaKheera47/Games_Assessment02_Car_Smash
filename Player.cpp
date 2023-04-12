#include <TL-Engine.h>
#include <iostream>
using namespace tle;

//#include "helpers.h";
#include "Player.h";
#include "dev.h";

// default constructor
Player::Player()
{
	m_model = nullptr;
	m_health = 0;
	m_currentSpeed = 0;
	m_maxSpeed = 0;
	m_acceleration = 0;
	m_deceleration = 0;
	m_rotationSpeed = 0;
	m_radius = 0;
}

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

	m_radius = sqrt((m_bbox.maxX * m_bbox.maxX) + (m_bbox.maxZ * m_bbox.maxZ));

	// get the wheels
	ISceneNode* FLWheel = m_model->GetNode(4);
	ISceneNode* FRWheel = m_model->GetNode(5);
	ISceneNode* BLWheel = m_model->GetNode(6);
	ISceneNode* BRWheel = m_model->GetNode(7);

	m_wheels[0] = FLWheel;
	m_wheels[1] = FRWheel;
	m_wheels[2] = BLWheel;
	m_wheels[3] = BRWheel;

	m_wheelRadius = 0.5f;
}

Player::~Player()
{
	// destructor
	m_health = 0;
	m_maxSpeed = 0;
	m_acceleration = 0;
	m_deceleration = 0;
	m_currentSpeed = 0;
	m_rotationSpeed = 0;
	m_bbox = {};
}

float GetRotationX(tle::ISceneNode* model)
{
	float matrix[4][4];
	model->GetMatrix(&matrix[0][0]);

	// Calculate the rotation angle from the matrix
	float rotationX = atan2f(matrix[1][2], matrix[2][2]) * (180.0f / kPi);

	return rotationX;
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

	// Calculate wheel rotation based on speed
	float wheelRotation = (m_currentSpeed * deltaTime) / (m_wheelRadius * 2.0f * kPi) * 360.0f;
	float steeringAngle = 0.0f;

	// pressing a rotates the model left
	if (myEngine->KeyHeld(Key_A))
	{
		m_model->RotateY(-m_rotationSpeed * m_currentSpeed * deltaTime);
		steeringAngle = -MAX_STEERING_ANGLE; // Adjust this value based on the desired steering angle
	}

	// pressing d rotates the model right
	if (myEngine->KeyHeld(Key_D))
	{
		m_model->RotateY(m_rotationSpeed * m_currentSpeed * deltaTime);
		steeringAngle = MAX_STEERING_ANGLE; // Adjust this value based on the desired steering angle
	}

	// Set the steering angle for the front wheels and keep the current rotation around the X-axis
	for (int i = 0; i < 2; ++i) {
		float currentXRotation = GetRotationX(m_wheels[i]);
		m_wheels[i]->ResetOrientation();
		m_wheels[i]->RotateY(steeringAngle);
		m_wheels[i]->RotateLocalX(currentXRotation);
	}

	// Rotate all wheels based on speed
	for (int i = 0; i < 4; ++i) {
		m_wheels[i]->RotateLocalX(wheelRotation);
	}
}

void Player::Bounce()
{
	if (m_currentSpeed > -CRAWL_SPEED && m_currentSpeed < CRAWL_SPEED) {
		return;
	}

	UndoLastMovement();
	// reverse direction, to simulate a bounce decrease by 75%
	SetSpeed(GetSpeed() * -0.75f);
}

SVector3 Player::GetPostion()
{
	return {
		m_model->GetX(),
		m_model->GetY(),
		m_model->GetZ()
	};
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

float Player::GetSpeed()
{
	return m_currentSpeed;
}

// get health
float Player::GetHealth()
{
	return m_health;
}

float Player::UpdateHealth(float health)
{
	m_health += health;
	return m_health;
}

BoundingBox Player::GetBBox()
{
	return m_bbox;
}

float Player::SetHealth(float health)
{
	m_health = health;
	return m_health;
}