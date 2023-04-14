#pragma once

#ifndef VARS
#define VARS

#include <TL-Engine.h>
using namespace tle;

// font options
constexpr int fontSize = 36;
const string fontName = "Red Hat Display";

// universal constants
const float kPi = 3.1415926f;

// enemy options
constexpr int numStaticEnemies = 4;
constexpr int numMovingEnemies = 4;
constexpr float ENEMY_RECOVERY_TIME = 15.0f;

constexpr float TEXT_PADDING = 10;

// locations
const SVector3 staticEnemyLocations[numStaticEnemies] = {
	{ -20, 0, 20 },
	{ 20, 0, 20 },
	{ -20, 0, -20 },
	{ 20, 0, -20 }
};

// moving cars
// initial position, min bound, max bound
const SVector3 movingEnemyLocations[numMovingEnemies][3] = {
	{
		{-30, 0, 15},
		{-30, 0, 15},
		{30, 0, 15}
	},
	{
		{30, 0, -15},
		{-30, 0, -15},
		{30, 0, -15},
	},
	{
		{30, 0, 30},
		{-30, 0, 30},
		{30, 0, 30},
	},
	{
		{-30, 0, -30},
		{-30, 0, -30},
		{30, 0, -30}
	},
};

const SVector3 ORIGIN = { 0, 0, 0 };
const SVector3 initPlayerLocation = ORIGIN;
const SVector3 skyboxLocation = { 0, -960.0f, 0 };

const float initPlayerSpeed = 0.0f;
const float CRAWL_SPEED = 0.5f;
const float maxPlayerSpeed = 30.0f;
const float MOVING_ENEMY_SPEED = maxPlayerSpeed * 0.5;
const float playerAcceleration = 0.20f;
const float playerDeceleration = 0.20f;
const float playerDrag = -playerAcceleration * 0.05f;
const float initPlayerHealth = 100.0f;
const float ROTATION_SPEED = 75.0f;
const float CAR_WHEEL_RADIUS = 0.5f;

const float MOMENTUM_FACTOR = 1.75f;
const float SPEED_DEADZONE = 0.1f;
const float BOUNCE_FACTOR = 0.75f;

const float perimeterRadius = 50.0f;
const int treeCount = 160;

// score
const float SIDE_IMPACT_SCORE_INCREASE = 15.0f;
const float FB_IMPACT_SCORE_INCREASE = 10.0f;

// game control keys
const EKeyCode K_WIDE_CAM = Key_1;
const EKeyCode K_CHASE_CAM = Key_2;
const EKeyCode K_FPP_CAM = Key_3;

const EKeyCode K_PAUSE = Key_P;
const EKeyCode K_QUIT = Key_Escape;
const EKeyCode K_RESTART = Key_R;

// camera options
const struct CAMERA_SETTING {
	SVector3 rotation;
	SVector3 position;
	bool isAnchored;
};

// moving enemy ball bouncing values
const float BOUNCE_SPEED = 1.5f;
const float BALL_BOUNCE_MAX = 5.5f;
const float BALL_BOUNCE_MIN = 2.5f;

const CAMERA_SETTING CAM_SETTING_WIDE = {
	{ 15.0f, 0, 0 },
	{ 0, 15.0f, -60.0f },
	false
};

const CAMERA_SETTING CAM_SETTING_CHASE = {
	{ 15.0f, 0, 0 },
	{ 0, 5.0f, -10.0f },
	true
};

const CAMERA_SETTING CAM_SETTING_FPP = {
	{ 0, 0, 0 },
	{ 0, 0.75f, 5 },
	true
};

// backdrop options
const string backdropName = "backdrop.jpg";
const float backdropWidth = 700;
const float backdropHeight = 60;

// damage values
const float OUT_OF_BOUNDS_DAMAGE = 10.0f;
// scaling on car model when hit
const float IMPACT_SCALE_FACTOR = 0.5f;

// particle options
const int P_NUM = 200;
const float P_EMIT_INTERVAL = 0.05;
const float P_LIFETIME = 0.5;
const float P_GRAVITY = -10.0f;
const float P_VERTICALITY = 3;
const float P_MIN_EMIT_INTERVAL = 0.0f; // Minimum time between emissions (e.g., when the player is at max speed)
const float P_MAX_EMIT_INTERVAL = 0.05f;  // Maximum time between emissions (e.g., when the player is stopped)

const float MAX_STEERING_ANGLE = 30.0f;

// movement angles
const float LEFTWARDS_ANGLE = -90.0f;
const float RIGHTWARDS_ANGLE = 90.0f;

// how far to move a model to calculate it's facing vector
const float FACING_VECTOR_OFFSET = 1.0f;

// used in truncate the decimal function
const int additionalLength = 1;

// static enemy BBox
const float STATIC_ENEMY_MIN_X = -0.946118f;
const float STATIC_ENEMY_MAX_X = 0.946118f;
const float STATIC_ENEMY_MIN_Y = 0.0065695f;
const float STATIC_ENEMY_MAX_Y = 1.50131f;
const float STATIC_ENEMY_MIN_Z = -1.97237f;
const float STATIC_ENEMY_MAX_Z = 1.97237f;

// Moving enemy BBox
const float MOVING_ENEMY_MIN_X = -0.946118f;
const float MOVING_ENEMY_MAX_X = 0.946118f;
const float MOVING_ENEMY_MIN_Y = 0.0065695f;
const float MOVING_ENEMY_MAX_Y = 1.50131f;
const float MOVING_ENEMY_MIN_Z = -1.97237f;
const float MOVING_ENEMY_MAX_Z = 1.97237f;

#endif // VARS
