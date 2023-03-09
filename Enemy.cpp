#include "Enemy.h";
#include <TL-Engine.h>
#include <iostream>
using namespace tle;

#include "helpers.h";
#include "enums.h";
#include "VARS.h"

Enemy::Enemy()
{
	m_carMesh = nullptr;
	m_ballMesh = nullptr;
	m_location = { 0, 0, 0 };
	m_hasEverBeenHit = false;
	m_carModel = nullptr;

	m_bbox = { -0.946118f, 0.946118f, 0.0065695f, 1.50131f, -1.97237f, 1.97237f };
}

Enemy::Enemy(IMesh* carMesh, IMesh* ballMesh, SVector3 location) {
	m_hasEverBeenHit = false;

	m_carMesh = carMesh;
	m_ballMesh = ballMesh;

	m_location = location;

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

Enemy::~Enemy()
{
	delete m_carModel;
	delete m_ballModel;
	m_location = {};
	m_hasEverBeenHit = false;
	m_bbox = {};
}

void Enemy::Create()
{
	m_carModel = m_carMesh->CreateModel(m_location.x, m_location.y, m_location.z);
	m_ballModel = m_ballMesh->CreateModel(0, 5, 0);
	m_ballModel->SetSkin("white.png");
	m_ballModel->AttachToParent(m_carModel);
}

void Enemy::HandleCollision(COLLISION_DIRECTION direction)
{
	if (m_hasEverBeenHit) return;

	m_hasEverBeenHit = true;
	m_ballModel->SetSkin("red.png");

	if (direction == SIDE_IMPACT)
	{
		scaleX(IMPACT_SCALE_FACTOR);
	}
	else if (direction == FB_IMPACT)
	{
		scaleZ(IMPACT_SCALE_FACTOR);
	}
}

bool Enemy::HasEverBeenHit()
{
	return m_hasEverBeenHit;
}

IModel* Enemy::GetModel()
{
	return m_carModel;
}

BoundingBox Enemy::GetBBox()
{
	return m_bbox;
}

void Enemy::scaleX(float factor)
{
	//declare a 4x4 matrix
	float matrix[4][4];

	//assign the car's matrix to the declared array 
	m_carModel->GetMatrix(&matrix[0][0]);

	// scale in x axis by the factor
	for (int i = 0; i < 4; i++)
	{
		matrix[0][i] *= factor;
	}

	//assign the array to the car's matrix
	m_carModel->SetMatrix(&matrix[0][0]);
}

void Enemy::scaleZ(float factor)
{
	//declare a 4x4 matrix
	float matrix[4][4];

	//assign the car's matrix to the declared array 
	m_carModel->GetMatrix(&matrix[0][0]);

	// scale in z axis by the factor
	for (int i = 0; i < 4; i++)
	{
		matrix[2][i] *= factor;
	}

	//assign the array to the car's matrix
	m_carModel->SetMatrix(&matrix[0][0]);
}
