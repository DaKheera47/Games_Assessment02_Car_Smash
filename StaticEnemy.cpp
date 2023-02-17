#include "StaticEnemy.h";
#include <TL-Engine.h>
#include <iostream>
using namespace tle;

#include "helpers.h";
#include "enums.h";

StaticEnemy::StaticEnemy()
{
	m_carMesh = nullptr;
	m_ballMesh = nullptr;
	m_location[0] = 0;
	m_location[1] = 0;
	m_location[2] = 0;
	m_hasEverBeenHit = false;
	m_carModel = nullptr;

	m_bbox = { -0.946118f, 0.946118f, 0.0065695f, 1.50131f, -1.97237f, 1.97237f };

	//float minX = -0.946118f;
	//float maxX = 0.946118f;
	//float minY = 0.0065695f;
	//float maxY = 1.50131f;
	//float minZ = -1.97237f;
	//float maxZ = 1.97237f;

	//m_bbox.minX = minX;
	//m_bbox.maxX = maxX;

	//m_bbox.minY = minY;
	//m_bbox.maxY = maxY;

	//m_bbox.minZ = minZ;
	//m_bbox.maxZ = maxZ;
}

StaticEnemy::StaticEnemy(IMesh* carMesh, IMesh* ballMesh, int location[3]) {
	m_hasEverBeenHit = false;

	m_carMesh = carMesh;
	m_ballMesh = ballMesh;

	m_location[0] = location[0];
	m_location[1] = location[1];
	m_location[2] = location[2];

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

StaticEnemy::~StaticEnemy()
{
}

void StaticEnemy::Create()
{
	m_carModel = m_carMesh->CreateModel(m_location[0], m_location[1], m_location[2]);
	m_ballModel = m_ballMesh->CreateModel(0, 5, 0);
	m_ballModel->SetSkin("white.jpg");
	m_ballModel->AttachToParent(m_carModel);
}

void StaticEnemy::HandleCollision()
{
	if (m_hasEverBeenHit == false) {
		m_hasEverBeenHit = true;
		m_ballModel->SetSkin("red.png");
	}
}

bool StaticEnemy::HasEverBeenHit()
{
	return m_hasEverBeenHit;
}

IModel* StaticEnemy::GetModel()
{
	return m_carModel;
}

BoundingBox StaticEnemy::GetBBox()
{
	return m_bbox;
}