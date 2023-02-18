#include <TL-Engine.h>
#include <sstream>
#include <cmath>
using namespace tle;

#include "Game.h";
#include "VARS.h";
#include "dev.h";
#include <iostream>

Game::Game(I3DEngine* myEngine)
{
	m_font = myEngine->LoadFont("Red Hat Display", 36);

	m_gameState = PLAYING;
	m_cameraAngle = CHASE;
	m_score = 0;

	m_font = myEngine->LoadFont(fontName, fontSize);

	// variables to draw text to the screen
	// get screen center coords
	m_screenWidth = myEngine->GetWidth();
	m_screenHeight = myEngine->GetHeight();
	// calculating half vertical and half horizontal from edges to position text in middle of the screen
	m_kScreenHorizHalf = m_screenWidth / 2, m_kScreenVertHalf = m_screenHeight / 2;
}

void Game::HandleGameStates(I3DEngine* myEngine, float deltaTime)
{
	//  Pressing the Escape key should quit the game.
	if (myEngine->KeyHit(Key_Escape))
	{
		myEngine->Stop();
	}

	// game pause case
	if (myEngine->KeyHit(Key_P))
	{
		// toggle paused state
		if (m_gameState == PAUSED)
		{
			m_gameState = PLAYING;
		}
		else if (m_gameState == PLAYING)
		{
			m_gameState = PAUSED;
		}
	}
}

void ApplyCameraSetting(CAMERA_SETTING setting, ICamera* camera, IModel* anchor)
{
	// reset orientation & position
	camera->ResetOrientation();
	camera->SetX(0);
	camera->SetY(0);
	camera->SetZ(0);

	// anchor to given anchor if required in the setting
	if (setting.isAnchored)
	{
		camera->AttachToParent(anchor);
	}
	else {
		camera->DetachFromParent();
	}

	// set new rotation & position
	camera->RotateLocalX(setting.rotation.x);
	camera->RotateLocalY(setting.rotation.y);
	camera->RotateLocalZ(setting.rotation.z);

	camera->SetLocalX(setting.position.x);
	camera->SetLocalY(setting.position.y);
	camera->SetLocalZ(setting.position.z);
}

void Game::HandleCameraAngles(I3DEngine* myEngine, ICamera* camera, IModel* anchor)
{
	const CAMERA_ANGLES prevAngle = m_cameraAngle;

	// switch to chase cam
	if (myEngine->KeyHit(K_CHASE_CAM))
	{
		m_cameraAngle = CHASE;
	}

	// switch to first person perspective
	if (myEngine->KeyHit(K_FPP_CAM))
	{
		m_cameraAngle = FPP;
	}

	// switch to wide cam
	if (myEngine->KeyHit(K_WIDE_CAM))
	{
		m_cameraAngle = WIDE;
	}

	// set specific camera settings, depending on the camera angle, based on the VARS.h file
	if (m_cameraAngle == CHASE)
	{
		ApplyCameraSetting(CAM_SETTING_CHASE, camera, anchor);
	}
	else if (m_cameraAngle == WIDE)
	{
		ApplyCameraSetting(CAM_SETTING_WIDE, camera, anchor);
	}
	else if (m_cameraAngle == FPP)
	{
		ApplyCameraSetting(CAM_SETTING_FPP, camera, anchor);
	}
}

float Game::UpdateScore(float score)
{
	m_score += score;
	return m_score;
}

float Game::GetScore()
{
	cout << "Score: " << to_string(round(m_score)) << endl;
	return round(m_score);
}

GAME_STATE Game::GetGameState()
{
	return m_gameState;
}

void Game::DrawText(float text, EHorizAlignment align)
{
	stringstream ss{};
	ss << text;

	cout << ss.str() << endl;

	if (!ss.str().empty())
	{
		m_font->Draw(ss.str(), 0, 0, kBlack, kLeft);
	}
}

void Game::DrawText(string text, EHorizAlignment align)
{
	stringstream ss{};
	ss << text;

	cout << ss.str() << endl;

	if (!ss.str().empty())
	{
		m_font->Draw(ss.str(), 0, 0, kBlack, kLeft);
	}
}
