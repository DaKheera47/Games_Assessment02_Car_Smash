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
constexpr float ENEMY_RECOVERY_TIME = 150.0f;

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
const float maxPlayerSpeed = 30.0f;
const float MOVING_ENEMY_SPEED = maxPlayerSpeed * 0.5;
const float playerAcceleration = 25.0f;
const float playerDeceleration = 20.0f;
const float initPlayerHealth = 100.0f;

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

#endif // VARS
