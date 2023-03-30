#pragma once

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

	// constructor to initialize all components to zero
	SVector3() : x(0.0f), y(0.0f), z(0.0f) {};

	// constructor to initialize all components to given values
	SVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};

	// overload subtraction operator to calculate vector difference
	SVector3 operator-(const SVector3& v2) const
	{
		return SVector3(x - v2.x, y - v2.y, z - v2.z);
	};

	// overload addition operator to calculate vector sum
	SVector3 operator+(const SVector3& v2) const
	{
		return SVector3(x + v2.x, y + v2.y, z + v2.z);
	};

	// overload multiplication operator to calculate scalar product
	SVector3 operator*(float scalar) const
	{
		return SVector3(x * scalar, y * scalar, z * scalar);
	};

	// overload division operator to calculate scalar division
	SVector3 operator/(float scalar) const
	{
		return SVector3(x / scalar, y / scalar, z / scalar);
	};

	// overload dot product operator
	float operator*(const SVector3& v2) const
	{
		return x * v2.x + y * v2.y + z * v2.z;
	};

	// calculate cross product of two vectors
	SVector3 CrossProduct(const SVector3& v2) const
	{
		return SVector3(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x);
	};

	// calculate length (magnitude) of vector
	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	};

	// normalize vector to unit length
	void Normalize()
	{
		float length = Length();
		if (length != 0.0f) {
			x /= length;
			y /= length;
			z /= length;
		}
	};
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
