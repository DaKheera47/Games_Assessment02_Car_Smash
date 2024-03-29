// Assessment2.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <array>
#include <sstream>
#include <ctime> // For time()
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
	// Seed the random number generator
	srand(static_cast<unsigned int>(time(nullptr)));

	// encapsulates most game states & other global actions
	Game game = Game();

	// frametime
	float frameTime = game.GetEngine()->Timer();

	// The main game loop, repeat until engine is stopped
	while (game.GetEngine()->IsRunning())
	{
		// K_QUIT to quit
		if (game.GetEngine()->KeyHit(K_QUIT))
		{
			game.GetEngine()->Stop();
		}

		// Draw the scene
		game.GetEngine()->DrawScene();

		// frametime
		frameTime = game.GetEngine()->Timer();

		// ask the game class to handle all game state changes
		game.HandleGameStates(frameTime);

		// don't calculate anything else
		if (game.GetGameState() == GAME_OVER)
		{
			game.RestartGame();
			// render game over text
			game.DrawText("Game Over", kCentre);
			// if game over, then don't update game elements
			continue;
		}
		else if (game.GetGameState() == GAME_WON)
		{
			game.RestartGame();
			// render game won text
			game.DrawText("Game Won", kCentre);
			// final score
			stringstream ss{};
			ss << "Final Score: " << game.GetScore();
			game.DrawText(ss.str(), kRight);
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
		game.HandleCameraAngles();

		// render score on screen
		game.DrawHUD();

		// handle player movement
		game.HandlePlayerMovement(frameTime);

		// check game overs
		if (game.CheckGameOver()) continue;

		// check game won
		if (game.CheckGameWon()) continue;

		// handle collisions
		game.HandleEnemyCollisions();

		// handling enemy movement each frame
		game.HandleEnemyMovement(frameTime);

		// handle the player going out of bounds
		game.ValidatePlayerPosition();

		// handle particle effects
		game.HandleParticles();
	}
}
