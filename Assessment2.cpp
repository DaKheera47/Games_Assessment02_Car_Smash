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

constexpr int fontSize = 36;
const string fontName = "Red Hat Display";
const int numStaticEnemies = 4;
const int numMovingEnemies = 4;

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
	IModel* ground = groundMesh->CreateModel(0, 0, 0);

	IMesh* skyboxMesh = myEngine->LoadMesh("skybox01.x");
	IModel* skybox = skyboxMesh->CreateModel(0, -960.0f, 0);

	IMesh* audiMesh = myEngine->LoadMesh("audi.x");
	IMesh* ballMesh = myEngine->LoadMesh("ball.x");

	// static cars
	SVector3 locations[numStaticEnemies] = {
		{ -20, 0, 20 },
		{ 20, 0, 20 },
		{ -20, 0, -20 }, 
		{ 20, 0, -20 }
	};

	StaticEnemy* staticEnemies[numStaticEnemies];

	for (int i = 0; i < numStaticEnemies; i++)
	{
		StaticEnemy* enemy = new StaticEnemy(audiMesh, ballMesh, locations[i]);
		staticEnemies[i] = enemy;

		// create all static enemies
		staticEnemies[i]->Create();
	}

	// moving cars
	// initial position, min bound, max bound
	SVector3 movingEnemyLocations[numMovingEnemies][3] = {
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

	// load estate.x
	IMesh* estateMesh = myEngine->LoadMesh("estate.x");

	MovingEnemy* movingEnemies[numMovingEnemies];

	for (int i = 0; i < numMovingEnemies; i++)
	{
		movingEnemies[i] = new MovingEnemy(estateMesh, ballMesh, movingEnemyLocations[i][0], movingEnemyLocations[i][1], movingEnemyLocations[i][2]);

		// create all moving enemies
		movingEnemies[i]->Create();
	}

	// create player
	IMesh* jeepMesh = myEngine->LoadMesh("4x4jeep.x");
	IModel* jeep = jeepMesh->CreateModel(0, 0, 0);
	Player player = Player(jeep, 100, 10, 50, 15, 10);

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
		if (game.GetGameState() == PAUSED)
		{
			// render game paused text
			game.DrawText("Game Paused", kCentre);
			// if paused, then don't update game elements
			continue;
		}

		// ask the game class to handle all camera angle changes
		game.HandleCameraAngles(myEngine, camera, player.GetModel());

		game.DrawText(game.GetScore(), kCentre);

		/**** Update your scene each frame here ****/
		player.HandleMovement(myEngine, frameTime);

		// check collision
		for (int i = 0; i < numStaticEnemies; i++)
		{
			StaticEnemy& currEnemy = *staticEnemies[i];

			bool isColliding = BoxToSphere(player.GetRadius(), player.GetModel(), currEnemy.GetModel(), currEnemy.GetBBox());

			if (!isColliding) continue;

			player.SetSpeed(0);
			player.UndoLastMovement();

			if (!currEnemy.HasEverBeenHit())
			{
				float dotProduct = calculateDotProduct(player.GetModel(), currEnemy.GetModel());

				if (dotProduct < 0.5 && dotProduct > -0.5)
				{
					game.UpdateScore(15.0f);
				}
				else {
					game.UpdateScore(10.0f);
				}
			}

			currEnemy.HandleCollision();
		}
	
		for (int i = 0; i < numMovingEnemies; i++)
		{
			MovingEnemy& currEnemy = *movingEnemies[i];

			currEnemy.HandleMovement(frameTime);
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
