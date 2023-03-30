#include "MovingEnemy.h";
#include <TL-Engine.h>
#include <iostream>
using namespace tle;

#include "helpers.h";
#include "enums.h";
#include "dev.h";
#include "VARS.h";

MovingEnemy::MovingEnemy(IMesh* carMesh, IMesh* ballMesh, SVector3 initialLocation, SVector3 minBound, SVector3 maxBound)
	: Enemy(carMesh, ballMesh, initialLocation) {
	float minX = -0.946118f;
	float maxX = 0.946118f;
	float minY = 0.0065695f;
	float maxY = 1.50131f;
	float minZ = -1.97237f;
	float maxZ = 1.97237f;

	m_bbox.minX = minX;
	m_bbox.maxX = maxX;

	m_bbox.minY = minY;
	m_bbox.maxY = maxY;

	m_bbox.minZ = minZ;
	m_bbox.maxZ = maxZ;

	m_minBound = minBound;
	m_maxBound = maxBound;
}

MovingEnemy::~MovingEnemy() {
	m_location = {};
	m_hasEverBeenHit = false;
	m_bbox = {};
	m_state = NOT_HIT;
	m_direction = RIGHT;
	m_timeSinceHit = 0;
	m_moveUp = false;
}

void MovingEnemy::FaceLeft(float frameTime)
{
	// reset rotation
	m_carModel->ResetOrientation();

	// rotate the enemy
	m_carModel->RotateY(-90.0f);
}

void MovingEnemy::FaceRight(float frameTime)
{
	// reset rotation
	m_carModel->ResetOrientation();

	// rotate the enemy
	m_carModel->RotateY(90.0f);
}

void MovingEnemy::HandleMovement(float frameTime)
{
	if (m_hasEverBeenHit) return;

	SVector3 currPostion = { m_carModel->GetX(), m_carModel->GetY(), m_carModel->GetZ() };

	if (currPostion.x < m_minBound.x) {
		m_direction = RIGHT;
	}

	if (currPostion.x > m_maxBound.x) {
		m_direction = LEFT;
	}

	if (m_direction == LEFT)
	{
		FaceLeft(frameTime);
	}
	else if (m_direction == RIGHT)
	{
		FaceRight(frameTime);
	}

	// Move the enemy left
	m_carModel->MoveLocalZ(MOVING_ENEMY_SPEED * frameTime);
}

void MovingEnemy::SetState(MOVING_ENEMY_STATE state)
{
	if (state == NOT_HIT)
	{
		m_hasEverBeenHit = false;
		m_ballModel->SetSkin("white.png");
		m_timeSinceHit = 0.0f;
	}
	else if (state == HIT)
	{
		m_hasEverBeenHit = true;
		m_ballModel->SetSkin("red.png");
	}
}

void MovingEnemy::BounceBall(float frameTime)
{
	if (m_ballModel->GetY() >= BALL_BOUNCE_MAX)
	{
		m_moveUp = false;
	}
	else if (m_ballModel->GetY() <= BALL_BOUNCE_MIN)
	{
		m_moveUp = true;
	}

	if (m_ballModel->GetY() <= BALL_BOUNCE_MIN && m_hasEverBeenHit)
	{
		m_ballModel->SetPosition(m_carModel->GetX(), BALL_BOUNCE_MIN, m_carModel->GetZ());
		m_moveUp = true;
		return;
	}

	if (m_moveUp)
	{
		// Move the ball up
		m_ballModel->MoveY(BOUNCE_SPEED * frameTime);
	}
	else {
		// Move the ball down
		m_ballModel->MoveY(-BOUNCE_SPEED * frameTime);
	}
}

SVector3 MovingEnemy::GetFacingVector()
{
	SVector3 facingVector = { 0, 0, 0 };

	// use the get facing vector function from helpers
	calculateFacingVector(m_carModel, facingVector);

	m_facingVector = facingVector;

	return m_facingVector;
}

void MovingEnemy::HandleCollision(bool isColliding, float frameTime)
{
	if (m_hasEverBeenHit)
	{
		m_timeSinceHit += frameTime;
	}

	if (m_timeSinceHit > ENEMY_RECOVERY_TIME) {
		SetState(NOT_HIT);
	}

	if (!isColliding) return;

	// if the enemy has been hit, and the time since the enemy has been hit is greater than 15 seconds, reset the enemy
	if (m_hasEverBeenHit == false) {
		SetState(HIT);
	}
}
