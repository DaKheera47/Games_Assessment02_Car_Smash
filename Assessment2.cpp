// Assessment2.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <array>
using namespace tle;

#include "Player.h";
#include "StaticEnemy.h"
#include "Assessment2.h";
#include "helpers.h";
#include "Game.h";
#include "MovingEnemy.h";
#include "VARS.h";

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder(".\\media");

	/**** Set up your scene here ****/
	IMesh* groundMesh = myEngine->LoadMesh("ground.x");
	IModel* ground = groundMesh->CreateModel(ORIGIN.x, ORIGIN.y, ORIGIN.z);

	IMesh* skyboxMesh = myEngine->LoadMesh("skybox01.x");
	IModel* skybox = skyboxMesh->CreateModel(skyboxLocation.x, skyboxLocation.y, skyboxLocation.z);

	IMesh* audiMesh = myEngine->LoadMesh("audi.x");
	IMesh* ballMesh = myEngine->LoadMesh("ball.x");

	// static cars
	StaticEnemy* staticEnemies[numStaticEnemies];

	for (int i = 0; i < numStaticEnemies; i++)
	{
		StaticEnemy* enemy = new StaticEnemy(audiMesh, ballMesh, staticEnemyLocations[i]);
		staticEnemies[i] = enemy;

		// create all static enemies
		staticEnemies[i]->Create();
	}

	// load estate.x
	IMesh* estateMesh = myEngine->LoadMesh("estate.x");

	// creating moving enemies
	MovingEnemy* movingEnemies[numMovingEnemies];
	for (int i = 0; i < numMovingEnemies; i++)
	{
		movingEnemies[i] = new MovingEnemy(estateMesh, ballMesh, movingEnemyLocations[i][0], movingEnemyLocations[i][1], movingEnemyLocations[i][2]);

		// create all moving enemies
		movingEnemies[i]->Create();
	}

	// create player
	IMesh* jeepMesh = myEngine->LoadMesh("caprice.x");
	IModel* jeep = jeepMesh->CreateModel(initPlayerLocation.x, initPlayerLocation.y, initPlayerLocation.z);
	Player player = Player(jeep, initPlayerHealth, initPlayerSpeed, maxPlayerSpeed, playerAcceleration, playerDeceleration);

	// creating a default camera
	ICamera* camera = myEngine->CreateCamera(kManual);

	// encapsulates most game states & other global actions
	Game game = Game(myEngine);

	// frametime
	float frameTime = myEngine->Timer();

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		// frametime
		frameTime = myEngine->Timer();

		// ask the game class to handle all game state changes
		game.HandleGameStates(myEngine, frameTime);

		// don't calculate anything else
		if (game.GetGameState() == GAME_OVER)
		{
			// render game over text
			game.DrawText("Game Over", kCentre);
			// if game over, then don't update game elements
			continue;
		}
		else if (game.GetGameState() == GAME_WON)
		{
			if (myEngine->KeyHit(K_RESTART))
			{
				// reset everything
				for (int i = 0; i < numStaticEnemies; i++)
				{
					// delete enemy at index
					delete staticEnemies[i];

					StaticEnemy* enemy = new StaticEnemy(audiMesh, ballMesh, staticEnemyLocations[i]);
					staticEnemies[i] = enemy;

					// create all static enemies
					staticEnemies[i]->Create();
				}

				for (int i = 0; i < numMovingEnemies; i++)
				{
					// delete enemy at index
					delete movingEnemies[i];

					movingEnemies[i] = new MovingEnemy(estateMesh, ballMesh, movingEnemyLocations[i][0], movingEnemyLocations[i][1], movingEnemyLocations[i][2]);

					// create all moving enemies
					movingEnemies[i]->Create();
				}

				// recreate player
				player.SetPosition(initPlayerLocation);
				//player.SetHealth(initPlayerHealth);
				player.SetSpeed(initPlayerSpeed);

				game.ResetScore();
				game.SetGameState(PLAYING);
			}

			// render game won text
			game.DrawText("Game Won", kCentre);
			// if game won, then don't update game elements
			continue;
		}
		else if (game.GetGameState() == PAUSED)
		{
			// render game paused text
			game.DrawText("Game Paused", kCentre);
			// if paused, then don't update game elements
			continue;
		}

		// ask the game class to handle all camera angle changes
		game.HandleCameraAngles(myEngine, camera, player.GetModel());

		// render score on screen
		game.DrawScore(kCentre);

		player.HandleMovement(myEngine, frameTime);

		// check if all static enemies are dead
		bool allEnemiesDead = true;
		for (int i = 0; i < numStaticEnemies; i++)
		{
			if (!staticEnemies[i]->HasEverBeenHit())
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
				if (!movingEnemies[i]->HasEverBeenHit())
				{
					allEnemiesDead = false;
					break;
				}
			}
		}

		// if all moving enemies are dead, then the player has won
		if (allEnemiesDead)
		{
			game.SetGameState(GAME_WON);
			// render game won text
			game.DrawText("You Won!", kCentre);
			// if won, then don't update game elements
			continue;
		}

		// check collision
		for (int i = 0; i < numStaticEnemies; i++)
		{
			StaticEnemy& currEnemy = *staticEnemies[i];

			bool isColliding = BoxToSphere(player.GetRadius(), player.GetModel(), currEnemy.GetModel(), currEnemy.GetBBox());

			if (!isColliding) continue;

			// reverse direction, to simulate a bounce decrease by 75%
			player.SetSpeed(player.GetSpeed() * -0.75f);

			// don't continue if this enemy has been hit before
			if (currEnemy.HasEverBeenHit()) continue;

			float dotProduct = calculateDotProduct(player.GetModel(), currEnemy.GetModel());

			if (dotProduct < 0.5 && dotProduct > -0.5)
			{
				game.UpdateScore(SIDE_IMPACT_SCORE_INCREASE);
			}
			else {
				game.UpdateScore(FB_IMPACT_SCORE_INCREASE);
			}

			currEnemy.HandleCollision();
		}

		for (int i = 0; i < numMovingEnemies; i++)
		{
			MovingEnemy& currEnemy = *movingEnemies[i];

			currEnemy.HandleMovement(frameTime);

			// check collision
			bool isColliding = BoxToSphere(player.GetRadius(), player.GetModel(), currEnemy.GetModel(), currEnemy.GetBBox());

			// don't continue if the enemy and player aren't colliding
			if (!isColliding) continue;

			// reverse direction, to simulate a bounce decrease by 75%
			player.SetSpeed(player.GetSpeed() * -0.75f);

			// don't continue if this enemy has been hit before
			if (currEnemy.HasEverBeenHit()) continue;

			// calculate dot product, and add points based on that
			float dotProduct = calculateDotProduct(player.GetModel(), currEnemy.GetModel());

			if (dotProduct < 0.5 && dotProduct > -0.5)
			{
				game.UpdateScore(SIDE_IMPACT_SCORE_INCREASE);
			}
			else {
				game.UpdateScore(FB_IMPACT_SCORE_INCREASE);
			}

			// handle collision
			currEnemy.HandleCollision(isColliding, frameTime);
		}
	}

	myEngine->Delete();
}
