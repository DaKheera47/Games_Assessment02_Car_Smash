#include <TL-Engine.h>
using namespace tle;

#include "enums.h";

#ifndef STATICENEMY_H
#define STATICENEMY_H

class StaticEnemy {
public:
	StaticEnemy();
	StaticEnemy(IMesh* carMesh, IMesh* ballMesh, int location[3]);
	~StaticEnemy();
	void HandleCollision();
	void Create();
	bool HasEverBeenHit();
	BoundingBox GetBBox();
	IModel* GetModel();

private:
	IMesh* m_carMesh;
	IMesh* m_ballMesh;
	int m_location[3];
	bool m_hasEverBeenHit;

	IModel* m_ballModel;
	IModel* m_carModel;

	BoundingBox m_bbox;
};

#endif // STATICENEMY_H
