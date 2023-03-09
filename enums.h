#ifndef ENUMS
#define ENUMS

enum BALL_COLORS { RED, WHITE };
enum GAME_STATE { GAME_WON, PLAYING, PAUSED, GAME_OVER };
enum CAMERA_ANGLES { FPP, CHASE, WIDE };
enum MOVEMENT_DIRECTION { LEFT, RIGHT };
enum MOVING_ENEMY_STATE { HIT, NOT_HIT };
enum COLLISION_DIRECTION { SIDE_IMPACT, FB_IMPACT };

struct SVector3
{
	float x;
	float y;
	float z;
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
