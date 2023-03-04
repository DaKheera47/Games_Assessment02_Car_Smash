#pragma once

#ifndef VARS
#define VARS

#include <TL-Engine.h>
using namespace tle;

// font options
constexpr int fontSize = 36;
const string fontName = "Red Hat Display";

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

const float initPlayerSpeed = 10.0f;
const float maxPlayerSpeed = 30.0f;
const float playerAcceleration = 25.0f;
const float playerDeceleration = 20.0f;
const float initPlayerHealth = 100.0f;

// score
const float SIDE_IMPACT_SCORE_INCREASE = 15.0f;
const float FB_IMPACT_SCORE_INCREASE = 10.0f;

// game control keys
const EKeyCode K_WIDE_CAM = Key_1;
const EKeyCode K_CHASE_CAM = Key_2;
const EKeyCode K_FPP_CAM = Key_3;

// camera options
const struct CAMERA_SETTING {
	SVector3 rotation;
	SVector3 position;
	bool isAnchored;
};

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

const string backdropName = "backdrop.jpg";
const float backdropWidth = 700;
const float backdropHeight = 60;


#endif // VARS
