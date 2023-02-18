#include <TL-Engine.h>
using namespace tle;

#include "enums.h";
#include "Enemy.h";

#ifndef MOVINGENEMY
#define MOVINGENEMY

class MovingEnemy : public Enemy {
public:
	MovingEnemy(IMesh* carMesh, IMesh* ballMesh, SVector3 location);
	void HandleMovement();
};

#endif // MOVINGENEMY
