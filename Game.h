
#ifndef GAME
#define GAME

#include <TL-Engine.h>
using namespace tle;

#include "enums.h";

class Game
{
public:
	Game()
	{
		m_gameState = PLAYING;
		m_cameraAngle = CHASE;
		m_score = 0;
	}

	GAME_STATE GetGameState();
	float GetScore();
	float UpdateScore(float score);
	
	void HandleKeypresses(I3DEngine* myEngine, float deltaTime);

	~Game()
	{
	}

private:
	GAME_STATE m_gameState;
	CAMERA_ANGLES m_cameraAngle;
	float m_score;

};


#endif // GAME