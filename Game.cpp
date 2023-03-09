#include <TL-Engine.h>
#include <sstream>
#include <cmath>
using namespace tle;

#include "Game.h";
#include "VARS.h";
#include "dev.h";
#include <iostream>
#include "helpers.h"

Game::Game()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	m_engine = New3DEngine(kTLX);
	m_engine->StartWindowed();

	// Add default folder for meshes and other media
	m_engine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	m_engine->AddMediaFolder(".\\media");

	m_font = m_engine->LoadFont("Red Hat Display", 36);

	m_gameState = PLAYING;
	m_cameraAngle = CHASE;
	m_score = 0;

	m_font = m_engine->LoadFont(fontName, fontSize);

	// variables to draw text to the screen
	// get screen center coords
	m_screenWidth = m_engine->GetWidth();
	m_screenHeight = m_engine->GetHeight();
	// calculating half vertical and half horizontal from edges to position text in middle of the screen
	m_screenHorizHalf = m_screenWidth / 2, m_screenVertHalf = m_screenHeight / 2;
	float halfBackdropWidth = backdropWidth / 2;

	// calculating the position
	float horizPos = m_screenHorizHalf - halfBackdropWidth;
	float vertPos = m_screenHeight - backdropHeight;

	// create and show backdrop.png as a sprite
	ISprite* backdrop = m_engine->CreateSprite(backdropName, horizPos, vertPos);

	/**** Set up your scene here ****/
	IMesh* groundMesh = m_engine->LoadMesh("ground.x");
	IModel* ground = groundMesh->CreateModel(ORIGIN.x, ORIGIN.y, ORIGIN.z);

	IMesh* skyboxMesh = m_engine->LoadMesh("skybox01.x");
	IModel* skybox = skyboxMesh->CreateModel(skyboxLocation.x, skyboxLocation.y, skyboxLocation.z);

	m_audiMesh = m_engine->LoadMesh("audi.x");
	m_ballMesh = m_engine->LoadMesh("ball.x");

	// static cars
	for (int i = 0; i < numStaticEnemies; i++)
	{
		StaticEnemy* enemy = new StaticEnemy(m_audiMesh, m_ballMesh, staticEnemyLocations[i]);
		m_staticEnemies[i] = enemy;

		// create all static enemies
		m_staticEnemies[i]->Create();
	}

	// load estate.x
	m_estateMesh = m_engine->LoadMesh("estate.x");

	// creating moving enemies
	for (int i = 0; i < numMovingEnemies; i++)
	{
		m_movingEnemies[i] = new MovingEnemy(m_estateMesh, m_ballMesh, movingEnemyLocations[i][0], movingEnemyLocations[i][1], movingEnemyLocations[i][2]);

		// create all moving enemies
		m_movingEnemies[i]->Create();
	}

	// create player
	IMesh* jeepMesh = m_engine->LoadMesh("4x4jeep.x");
	IModel* jeep = jeepMesh->CreateModel(initPlayerLocation.x, initPlayerLocation.y, initPlayerLocation.z);
	m_player = Player(jeep, initPlayerHealth, initPlayerSpeed, maxPlayerSpeed, playerAcceleration, playerDeceleration);

	// creating a default camera
	m_camera = m_engine->CreateCamera(kManual);

	float degrees = 0.0f;

	IMesh* treeMesh = m_engine->LoadMesh("tree.x");
	// make array of Tree
	Tree trees[treeCount]{};

	for (int i = 0; i < treeCount; i++)
	{
		float radians = kPi / 180 * degrees;
		float x = perimeterRadius * cos(radians);
		float y = perimeterRadius * sin(radians);

		// create tree
		trees[i].model = treeMesh->CreateModel(x, 0, y);
		trees[i].angle = degrees;

		// increment degrees
		degrees += (360 / treeCount) + 2;
	}
}

void Game::HandleGameStates(float deltaTime)
{
	// game pause case
	if (m_engine->KeyHit(K_PAUSE))
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

void Game::SetGameState(GAME_STATE gameState)
{
	m_gameState = gameState;
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

void Game::HandleCameraAngles()
{
	const CAMERA_ANGLES prevAngle = m_cameraAngle;
	IModel* anchor = m_player.GetModel();

	// switch to chase cam
	if (m_engine->KeyHit(K_CHASE_CAM))
	{
		m_cameraAngle = CHASE;
	}

	// switch to first person perspective
	if (m_engine->KeyHit(K_FPP_CAM))
	{
		m_cameraAngle = FPP;
	}

	// switch to wide cam
	if (m_engine->KeyHit(K_WIDE_CAM))
	{
		m_cameraAngle = WIDE;
	}

	// set specific camera settings, depending on the camera angle, based on the VARS.h file
	if (m_cameraAngle == CHASE)
	{
		ApplyCameraSetting(CAM_SETTING_CHASE, m_camera, anchor);
	}
	else if (m_cameraAngle == WIDE)
	{
		ApplyCameraSetting(CAM_SETTING_WIDE, m_camera, anchor);
	}
	else if (m_cameraAngle == FPP)
	{
		ApplyCameraSetting(CAM_SETTING_FPP, m_camera, anchor);
	}
}

float Game::UpdateScore(float score)
{
	m_score += score;
	return m_score;
}

float Game::GetScore()
{
	return round(m_score);
}

GAME_STATE Game::GetGameState()
{
	return m_gameState;
}

I3DEngine* Game::GetEngine()
{
	return m_engine;
}

void Game::DrawText(float text, EHorizAlignment align)
{
	stringstream ss{};
	ss << text;
	// position it perfectly in the middle of the backdrop image
	float m_textVertPos = m_screenHeight - (backdropHeight / 1.25);

	if (!ss.str().empty())
	{
		if (align == kCentre)
		{
			m_font->Draw(ss.str(), m_screenHorizHalf, m_textVertPos, kBlack, kCentre);
		}
		else if (align == kLeft)
		{
			m_font->Draw(ss.str(), m_screenHorizHalf - (backdropWidth / 2) + TEXT_PADDING, m_textVertPos, kBlack, kLeft);
		}
		else if (align == kRight)
		{
			m_font->Draw(ss.str(), m_screenHorizHalf + (backdropWidth / 2) - TEXT_PADDING, m_textVertPos, kBlack, kRight);
		}
	}
}

void Game::DrawText(string text, EHorizAlignment align)
{
	stringstream ss{};
	ss << text;
	// position it perfectly in the middle of the backdrop image
	float m_textVertPos = m_screenHeight - (backdropHeight / 1.25);

	if (!ss.str().empty())
	{
		if (align == kCentre)
		{
			m_font->Draw(ss.str(), m_screenHorizHalf, m_textVertPos, kBlack, kCentre);
		}
		else if (align == kLeft)
		{
			m_font->Draw(ss.str(), m_screenHorizHalf - (backdropWidth / 2) + TEXT_PADDING, m_textVertPos, kBlack, kLeft);
		}
		else if (align == kRight)
		{
			m_font->Draw(ss.str(), m_screenHorizHalf + (backdropWidth / 2) - TEXT_PADDING, m_textVertPos, kBlack, kRight);
		}
	}
}

void Game::DrawHUD()
{
	stringstream ss{};

	ss << "Score: " << m_score;
	DrawText(ss.str(), kCentre);

	ss.str("");
	ss << "Health: " << m_player.GetHealth();
	DrawText(ss.str(), kLeft);
}

void Game::ResetScore()
{
	m_score = 0;
}

void Game::RestartGame()
{
	if (m_engine->KeyHit(K_RESTART))
	{
		if (m_gameState != GAME_OVER && m_gameState != GAME_WON)
		{
			// skip if statement
			return;
		}

		// reset everything
		for (int i = 0; i < numStaticEnemies; i++)
		{
			// delete enemy at index
			delete m_staticEnemies[i];

			StaticEnemy* enemy = new StaticEnemy(m_audiMesh, m_ballMesh, staticEnemyLocations[i]);
			m_staticEnemies[i] = enemy;

			// create all static enemies
			m_staticEnemies[i]->Create();
		}

		for (int i = 0; i < numMovingEnemies; i++)
		{
			// delete enemy at index
			delete m_movingEnemies[i];

			m_movingEnemies[i] = new MovingEnemy(m_estateMesh, m_ballMesh, movingEnemyLocations[i][0], movingEnemyLocations[i][1], movingEnemyLocations[i][2]);

			// create all moving enemies
			m_movingEnemies[i]->Create();
		}

		// recreate player
		m_player.SetPosition(initPlayerLocation);
		m_player.SetHealth(initPlayerHealth);
		m_player.SetSpeed(initPlayerSpeed);
		m_player.GetModel()->ResetOrientation();

		ResetScore();
		m_gameState = PLAYING;
	}
}

void Game::HandlePlayerMovement(float deltaTime)
{
	m_player.HandleMovement(m_engine, deltaTime);
}

bool Game::CheckGameOver()
{
	// check if player health is below or equal to 0
	if (m_player.GetHealth() <= 0)
	{
		m_gameState = GAME_OVER;
		// render game over text
		DrawText("Game Over", kCentre);
		// if game over, then don't update game elements
		return true;
	}

	return false;
}

bool Game::CheckGameWon()
{
	// check if all static enemies are dead
	bool allEnemiesDead = true;
	for (int i = 0; i < numStaticEnemies; i++)
	{
		if (!m_staticEnemies[i]->HasEverBeenHit())
		{
			allEnemiesDead = false;
			break;
		}
	}

	// only check moving enemies if all static enemies are dead
	if (allEnemiesDead)
	{
		// check if all moving enemies are dead
		for (int i = 0; i < numMovingEnemies; i++)
		{
			if (!m_movingEnemies[i]->HasEverBeenHit())
			{
				allEnemiesDead = false;
				break;
			}
		}
	}

	// if all moving enemies are dead, then the m_player has won
	if (allEnemiesDead)
	{
		m_gameState = GAME_WON;
		// render game won text
		DrawText("You Won!", kCentre);
		// if won, then don't update game elements
		return true;
	}

	return false;
}

void Game::ValidatePlayerPosition()
{
	const SVector3 playerPos = m_player.GetPostion();

	// distance between 0,0,0 and player
	float distance = calculateDistance({ 0,0,0 }, playerPos);

	// if distance is greater than perimeterRadius, bounce the player
	if (distance + m_player.GetRadius() > perimeterRadius)
	{
		m_player.Bounce();
		m_player.UpdateHealth(-OUT_OF_BOUNDS_DAMAGE);
	}
}

void Game::HandleStaticCollisions()
{
	// check collision
	for (int i = 0; i < numStaticEnemies; i++)
	{
		StaticEnemy& currEnemy = *m_staticEnemies[i];

		bool isColliding = BoxToSphere(m_player.GetRadius(), m_player.GetModel(), currEnemy.GetModel(), currEnemy.GetBBox());

		if (!isColliding) continue;

		// reverse direction, to simulate a bounce decrease by 75%
		m_player.Bounce();

		// don't continue if this enemy has been hit before
		if (currEnemy.HasEverBeenHit()) continue;

		// calculate dot product, and then give score based on that
		float dotProduct = calculateDotProduct(m_player.GetModel(), currEnemy.GetModel());

		if (dotProduct < 0.5 && dotProduct > -0.5)
		{
			m_score += SIDE_IMPACT_SCORE_INCREASE;
			currEnemy.HandleCollision(SIDE_IMPACT);
		}
		else {
			m_score += FB_IMPACT_SCORE_INCREASE;
			currEnemy.HandleCollision(FB_IMPACT);
		}
	}
}

void Game::HandleMovingCollisions(float deltaTime)
{
	for (int i = 0; i < numMovingEnemies; i++)
	{
		MovingEnemy& currEnemy = *m_movingEnemies[i];

		currEnemy.HandleMovement(deltaTime);
		currEnemy.BounceBall(deltaTime);

		// check collision
		bool isColliding = BoxToSphere(m_player.GetRadius(), m_player.GetModel(), currEnemy.GetModel(), currEnemy.GetBBox());

		// don't continue if the enemy and player aren't colliding
		if (!isColliding) continue;

		// reverse direction, to simulate a bounce decrease by 75%
		m_player.Bounce();

		// don't continue if this enemy has been hit before
		if (currEnemy.HasEverBeenHit()) continue;

		// calculate dot product, and add points based on that
		float dotProduct = calculateDotProduct(m_player.GetModel(), currEnemy.GetModel());

		if (dotProduct < 0.5 && dotProduct > -0.5)
		{
			m_score += SIDE_IMPACT_SCORE_INCREASE;
		}
		else {
			m_score += FB_IMPACT_SCORE_INCREASE;
		}

		// handle collision
		currEnemy.HandleCollision(isColliding, deltaTime);
	}

}