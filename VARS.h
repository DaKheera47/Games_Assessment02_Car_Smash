#ifndef VARS
#define VARS

#include <TL-Engine.h>
using namespace tle;
#include "enums.h";


// game control keys
EKeyCode K_WIDE_CAM = Key_1;
EKeyCode K_CHASE_CAM = Key_2;
EKeyCode K_FPP_CAM = Key_3;

// camera options
struct CAMERA_SETTING {
	SVector3 rotation;
	SVector3 position;
	bool isAnchored;
};

CAMERA_SETTING CAM_SETTING_WIDE = {
	{ 15.0f, 0, 0 },
	{ 0, 15.0f, -60.0f },
	false
};

CAMERA_SETTING CAM_SETTING_CHASE = {
	{ 15.0f, 0, 0 },
	{ 0, 5.0f, -10.0f },
	true
};

CAMERA_SETTING CAM_SETTING_FPP = {
	{ 0, 0, 0 },
	{ 0, 0.75f, 6 },
	true
};



#endif // VARS