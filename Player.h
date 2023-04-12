#ifndef PLAYER
#define PLAYER

#include <TL-Engine.h>
#include <vector>
using namespace tle;

#include "enums.h";
#include "VARS.h";


class Player
{
public:
	// default constructor
	Player();
	// constructor
	Player(IModel* model, float health, float currentSpeed, float maxSpeed, float acceleration, float deceleration);

	// destructor
	~Player();

	// functions
	void HandleMovement(I3DEngine* myEngine, float deltaTime);
	IModel* GetModel();
	float GetRadius();
	void SetPosition(SVector3 position);
	void SetSpeed(float speed);
	void UndoLastMovement();
	float Player::GetSpeed();
	void Bounce();
	float GetHealth();
	BoundingBox GetBBox();
	float UpdateHealth(float health);
	float SetHealth(float health);

	SVector3 GetPostion();

private:
	float m_health;
	float m_maxSpeed;
	float m_acceleration;
	float m_deceleration;
	float m_currentSpeed;
	float m_rotationSpeed;
	float m_radius;
	float m_wheelRadius;
	float m_thrustScale = 100.0f;

	float m_frictionCoefficient = 0.005f;

	SVector3 m_thrust, m_momentum, m_oldMomentum, m_drag = { 0, 0, 0 };

	ISceneNode* m_wheels[4];

	SVector3 m_prevPosition;

	IModel* m_model;
	BoundingBox m_bbox;
};




#endif // PLAYER
