
#ifndef GAME
#define GAME

#include <TL-Engine.h>
using namespace tle;

#include "enums.h";

class Game
{
public:
	Game();

	GAME_STATE GetGameState();
	float GetScore();
	float UpdateScore(float score);

	void HandleGameStates(I3DEngine* myEngine, float deltaTime);
	void HandleCameraAngles(I3DEngine* myEngine, ICamera* camera, IModel* anchor);

	~Game()
	{
	}

private:
	GAME_STATE m_gameState;
	CAMERA_ANGLES m_cameraAngle;
	float m_score;

};


#endif // GAME