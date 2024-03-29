#include <TL-Engine.h>
using namespace tle;

#include "enums.h";

#ifndef ENEMY
#define ENEMY

class Enemy {
public:
	Enemy();
	Enemy(IMesh* carMesh, IMesh* ballMesh, SVector3 location);

	~Enemy();
	void HandleCollision(COLLISION_DIRECTION direction);
	void Create();
	bool HasEverBeenHit();
	void scaleX(float factor);
	void scaleZ(float factor);
	BoundingBox GetBBox();
	IModel* GetModel();

	IMesh* m_carMesh;
	IMesh* m_ballMesh;
	SVector3 m_location;
	bool m_hasEverBeenHit;

	IModel* m_ballModel;
	IModel* m_carModel;

	BoundingBox m_bbox;
};

#endif // ENEMY
