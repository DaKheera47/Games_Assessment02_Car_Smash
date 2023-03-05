#ifndef PLAYER
#define PLAYER

#include <TL-Engine.h>
using namespace tle;

#include "enums.h";


class Player
{
public:
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

	SVector3 GetPostion();

private:
	float m_health;
	float m_maxSpeed;
	float m_acceleration;
	float m_deceleration;
	float m_currentSpeed;
	float m_rotationSpeed;
	float m_radius;

	SVector3 m_prevPosition;
	
	IModel* m_model;
	BoundingBox m_bbox;
};




#endif // PLAYER
