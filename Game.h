
#ifndef GAME
#define GAME

#include <TL-Engine.h>
using namespace tle;

#include "enums.h";
#include "StaticEnemy.h"
#include "MovingEnemy.h"
#include "Player.h";
#include "VARS.h";
#include "Emitter.h";

class Game
{
public:
	Game::Game();

	GAME_STATE GetGameState();
	I3DEngine* GetEngine();
	float GetScore();
	float UpdateScore(float score);

	void HandleGameStates(float deltaTime);
	void HandlePlayerMovement(float deltaTime);
	void SetGameState(GAME_STATE gameState);
	void ResetScore();
	void HandleCameraAngles();

	void DrawText(string text, EHorizAlignment align);
	void DrawText(float text, EHorizAlignment align);
	void DrawHUD();

	bool CheckGameOver();
	bool CheckGameWon();

	void RestartGame();
	void ValidatePlayerPosition();

	// collisions
	void HandleEnemyCollisions();
	void HandleMovingCollisions(float deltaTime);
	void HandleEnemyMovement(float deltatTime);

	// particle effects
	void emitParticle(Particle& p, const SVector3& position, float lifetime, const SVector3& movementVector);
	void HandleParticles();

	~Game()
	{
	}

private:
	GAME_STATE m_gameState;
	CAMERA_ANGLES m_cameraAngle;
	float m_score;

	IFont* m_font;
	float m_frametime;

	// variables to draw text to the screen
	float m_screenWidth;
	float m_screenHeight;
	float m_screenHorizHalf;
	float m_screenVertHalf;

	I3DEngine* m_engine;
	Player m_player;
	ICamera* m_camera;

	// enemy arrays
	StaticEnemy* m_staticEnemies[numStaticEnemies];
	MovingEnemy* m_movingEnemies[numMovingEnemies];

	// meshes
	IMesh* m_estateMesh;
	IMesh* m_audiMesh;
	IMesh* m_ballMesh;

	// particle effects
	Emitter m_leftEmitter;
	Emitter m_rightEmitter;
	IMesh* m_sphereMesh;
};


#endif // GAME