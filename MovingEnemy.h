#include <TL-Engine.h>
using namespace tle;

#include "enums.h";
#include "Enemy.h";

#ifndef MOVINGENEMY
#define MOVINGENEMY

class MovingEnemy : public Enemy {
public:
	MovingEnemy(IMesh* carMesh, IMesh* ballMesh, SVector3 initialLocation, SVector3 minBound, SVector3 maxBound);
	~MovingEnemy();
	void HandleMovement(float frameTime);
	void HandleCollision(bool isColliding, float frameTime);
	void FaceLeft(float frameTime);
	void FaceRight(float frameTime);
	void SetState(MOVING_ENEMY_STATE state);
	void BounceBall(float frameTime);

private:
	MOVEMENT_DIRECTION m_direction = RIGHT;
	SVector3 m_minBound;
	SVector3 m_maxBound;
	float m_timeSinceHit = 0;
	MOVING_ENEMY_STATE m_state = NOT_HIT;

	bool m_moveUp = false;
};

#endif // MOVINGENEMY
