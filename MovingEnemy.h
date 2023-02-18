#include <TL-Engine.h>
using namespace tle;

#include "enums.h";
#include "Enemy.h";

#ifndef MOVINGENEMY
#define MOVINGENEMY

class MovingEnemy : public Enemy {
public:
	MovingEnemy(IMesh* carMesh, IMesh* ballMesh, SVector3 initialLocation, SVector3 minBound, SVector3 maxBound);
	void HandleMovement(float frameTime);
	void FaceLeft(float frameTime);
	void FaceRight(float frameTime);

private:
	DIRECTION m_direction = RIGHT;
	SVector3 m_minBound;
	SVector3 m_maxBound;
};

#endif // MOVINGENEMY
