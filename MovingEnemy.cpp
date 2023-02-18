#include "MovingEnemy.h";
#include <TL-Engine.h>
#include <iostream>
using namespace tle;

#include "helpers.h";
#include "enums.h";
#include "dev.h"

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
	m_carModel->MoveLocalZ(5.0f * frameTime);
}
