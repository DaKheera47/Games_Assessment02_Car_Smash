#include "Game.h";
#include <TL-Engine.h>
using namespace tle;

void Game::HandleKeypresses(I3DEngine* myEngine, float deltaTime)
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

float Game::UpdateScore(float score)
{
	m_score += score;
	return m_score;
}

float Game::GetScore()
{
	return m_score;
}

GAME_STATE Game::GetGameState()
{
	return m_gameState;
}
