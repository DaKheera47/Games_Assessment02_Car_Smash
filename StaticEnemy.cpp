#include "StaticEnemy.h";
#include <TL-Engine.h>
#include <iostream>
using namespace tle;

#include "helpers.h";
#include "enums.h";

StaticEnemy::StaticEnemy(IMesh* carMesh, IMesh* ballMesh, SVector3 location) : Enemy(carMesh, ballMesh, location) {
	m_bbox = {
		STATIC_ENEMY_MIN_X,
		STATIC_ENEMY_MAX_X,
		STATIC_ENEMY_MIN_Y,
		STATIC_ENEMY_MAX_Y,
		STATIC_ENEMY_MIN_Z,
		STATIC_ENEMY_MAX_Z
	};
}
