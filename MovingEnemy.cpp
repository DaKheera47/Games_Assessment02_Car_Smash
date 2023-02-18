#include "MovingEnemy.h";
#include <TL-Engine.h>
#include <iostream>
using namespace tle;

#include "helpers.h";
#include "enums.h";

MovingEnemy::MovingEnemy(IMesh* carMesh, IMesh* ballMesh, SVector3 location)
	: Enemy(carMesh, ballMesh, location) {
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
}

void MovingEnemy::HandleMovement()
{
	// Move the enemy forward
	m_carModel->MoveLocalZ(0.01f);

	// If the enemy is off the track, move it back to the start
	if (m_carModel->GetX() > 100 || m_carModel->GetX() < -100 || m_carModel->GetZ() > 100 || m_carModel->GetZ() < -100) {
		m_carModel->SetPosition(0, 0, 0);
	}
}
