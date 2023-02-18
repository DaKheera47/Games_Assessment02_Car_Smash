#include <TL-Engine.h>
using namespace tle;

#include "enums.h";
#include "Enemy.h";

#ifndef STATICENEMY_H
#define STATICENEMY_H

class StaticEnemy : public Enemy {
public:
	StaticEnemy(IMesh* carMesh, IMesh* ballMesh, SVector3 location);
};

#endif // STATICENEMY_H
