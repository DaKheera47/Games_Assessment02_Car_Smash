
#ifndef GAME
#define GAME

#include <TL-Engine.h>
using namespace tle;

#include "enums.h";

class Game
{
public:
	Game::Game(I3DEngine* myEngine);

	GAME_STATE GetGameState();
	float GetScore();
	float UpdateScore(float score);

	void HandleGameStates(I3DEngine* myEngine, float deltaTime);
	void SetGameState(GAME_STATE gameState);
	void HandleCameraAngles(I3DEngine* myEngine, ICamera* camera, IModel* anchor);

	void DrawText(string text, EHorizAlignment align);
	void DrawText(float text, EHorizAlignment align);

	void DrawScore(EHorizAlignment align);

	~Game()
	{
	}

private:
	GAME_STATE m_gameState;
	CAMERA_ANGLES m_cameraAngle;
	float m_score;

	IFont* m_font;

	// variables to draw text to the screen
	float m_screenWidth;
	float m_screenHeight;
	float m_screenHorizHalf;
	float m_screenVertHalf;
};


#endif // GAME