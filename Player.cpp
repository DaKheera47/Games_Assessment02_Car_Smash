#include <TL-Engine.h>
#include <iostream>
using namespace tle;

//#include "helpers.h";
#include "Player.h";
#include "dev.h";
#include "helpers.h"

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
	m_rotationSpeed = ROTATION_SPEED;

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

	float carPos[4][4];
	m_model->GetMatrix(&carPos[0][0]);
	SVector3 localZ = { carPos[2][0], carPos[2][1], carPos[2][2] };

	if (myEngine->KeyHeld(Key_W))
	{
		m_thrust = { localZ.x * m_acceleration, localZ.y * m_acceleration, localZ.z * m_acceleration };
	}
	else if (myEngine->KeyHeld(Key_S))
	{
		m_thrust = { localZ.x * -m_deceleration, localZ.y * -m_deceleration, localZ.z * -m_deceleration };
	}
	else
	{
		m_thrust = { 0, 0, 0 };
	}

	m_drag = {
		m_oldMomentum.x * playerDrag,
		m_oldMomentum.y * playerDrag,
		m_oldMomentum.z * playerDrag
	};

	m_momentum = {
		m_thrust.x + m_oldMomentum.x + m_drag.x,
		m_thrust.y + m_oldMomentum.y + m_drag.y,
		m_thrust.z + m_oldMomentum.z + m_drag.z
	};

	m_oldMomentum = m_momentum;

	// move model
	m_model->Move((m_momentum.x * MOMENTUM_FACTOR) * deltaTime, (m_momentum.y * MOMENTUM_FACTOR) * deltaTime, (m_momentum.z * MOMENTUM_FACTOR) * deltaTime);

	m_currentSpeed = sqrt(m_momentum.x * m_momentum.x + m_momentum.y * m_momentum.y + m_momentum.z * m_momentum.z);

	if (m_currentSpeed <= SPEED_DEADZONE && m_currentSpeed >= -SPEED_DEADZONE) return;

	// Calculate wheel rotation based on speed
	float wheelRotation = (m_currentSpeed * deltaTime) / (m_wheelRadius * 2.0f * kPi) * 360.0f;
	float steeringAngle = 0.0f;

	// pressing a rotates the model left
	if (myEngine->KeyHeld(Key_A))
	{
		m_model->RotateY(-m_rotationSpeed * deltaTime);
		steeringAngle = -MAX_STEERING_ANGLE; // Adjust this value based on the desired steering angle
	}

	// pressing d rotates the model right
	if (myEngine->KeyHeld(Key_D))
	{
		m_model->RotateY(m_rotationSpeed * deltaTime);
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

void Player::Bounce(COLLISION_AXIS axis)
{
	m_oldMomentum.x *= -1 * 0.75;
	m_oldMomentum.z *= -1 * 0.75;
}

void Player::HandleCollision(MovingEnemy& enemy, float frametime, float& score)
{
	COLLISION_AXIS collisionAxis = BoxToSphere(m_radius, m_model, enemy.GetModel(), enemy.GetBBox());

	enemy.HandleCollision(collisionAxis != NONE, frametime);

	if (collisionAxis == NONE) return;

	// reverse direction, to simulate a bounce decrease by 75%
	Bounce(collisionAxis);

	// don't continue if this enemy has been hit before
	if (enemy.HasEverBeenHit()) return;

	// calculate dot product, and then give score based on that
	float dotProduct = calculateDotProduct(m_model, enemy.GetModel());

	if (dotProduct < 0.5 && dotProduct > -0.5)
	{
		score += SIDE_IMPACT_SCORE_INCREASE;
	}
	else {
		score += FB_IMPACT_SCORE_INCREASE;
	}
}


void Player::HandleCollision(StaticEnemy& enemy, float frametime, float& score)
{
	COLLISION_AXIS collisionAxis = BoxToSphere(m_radius, m_model, enemy.GetModel(), enemy.GetBBox());

	if (collisionAxis == NONE) return;

	// reverse direction, to simulate a bounce decrease by 75%
	Bounce(collisionAxis);

	// don't continue if this enemy has been hit before
	if (enemy.HasEverBeenHit()) return;

	// calculate dot product, and then give score based on that
	float dotProduct = calculateDotProduct(m_model, enemy.GetModel());

	if (dotProduct < 0.5 && dotProduct > -0.5)
	{
		score += SIDE_IMPACT_SCORE_INCREASE;
		enemy.HandleCollision(SIDE_IMPACT);
	}
	else {
		score += FB_IMPACT_SCORE_INCREASE;
		enemy.HandleCollision(FB_IMPACT);
	}
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