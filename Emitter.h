#pragma once

#include <TL-Engine.h>
#include "enums.h"
#include "helpers.h"
#include "Player.h"
#include "VARS.h"
using namespace tle;

#ifndef EMITTER_H
#define EMITTER_H

class Emitter
{
public:
	Emitter();
	Emitter(I3DEngine* myEngine, Player& player);
	~Emitter() = default;
	void Update(float frametime, SVector3 emitterPos, I3DEngine* myEngine, IMesh* sphereMesh, SVector3 playerPos, float speedPercentage);

	void emitParticle(Particle& p, const SVector3& position, float lifetime, const SVector3& movementVector);

private:
	Particle m_particles[P_NUM];
	int m_verticality;
};

#endif // EMITTER_H