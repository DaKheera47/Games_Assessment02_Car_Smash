#include <TL-Engine.h>
using namespace tle;

#ifndef ENUMS
#define ENUMS

enum BALL_COLORS { RED, WHITE };
enum GAME_STATE { GAME_WON, PLAYING, PAUSED, GAME_OVER };
enum CAMERA_ANGLES { FPP, CHASE, WIDE };
enum MOVEMENT_DIRECTION { LEFT, RIGHT };
enum MOVING_ENEMY_STATE { HIT, NOT_HIT };
enum COLLISION_DIRECTION { SIDE_IMPACT, FB_IMPACT };

struct SVector3 {
	float x = 0;
	float y = 0;
	float z = 0;
};

struct SVector2 {
	float x;
	float y;
};

struct Particle {
	IModel* model;
	SVector3 movementVector;
	bool isEmitted = false;
	float lifetime = 0.0f;
};

struct BoundingBox {
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;
};

struct Tree {
	IModel* model;
	float angle;
};

#endif // ENUMS
