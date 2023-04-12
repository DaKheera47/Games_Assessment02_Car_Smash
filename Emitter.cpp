#include "Emitter.h"
#include <iostream>

void Emitter::emitParticle(Particle& p, const SVector3& position, float lifetime, const SVector3& movementVector) {
	if (p.model == nullptr) return;

	p.model->SetPosition(position.x, position.y, position.z);
	p.movementVector = movementVector;
	p.isEmitted = true;
	p.lifetime = lifetime;
}

Emitter::Emitter()
{
	for (int i = 0; i < P_NUM; i++)
	{
		m_particles[i].model = nullptr;
		m_particles[i].isEmitted = false;
		m_particles[i].lifetime = P_LIFETIME;
	}
}

Emitter::Emitter(I3DEngine* myEngine, Player& player)
{

}

void Emitter::Update(float frametime, SVector3 emitterPos, I3DEngine* myEngine, IMesh* sphereMesh, SVector3 playerPos, float speedPercentage)
{
	static float timeSinceLastEmit = 0.0f;
	timeSinceLastEmit += frametime;

	for (int i = 0; i < P_NUM; ++i) {
		Particle& p = m_particles[i];

		if (p.model == nullptr) {
			for (int i = 0; i < P_NUM; i++)
			{
				m_particles[i].model = sphereMesh->CreateModel(playerPos.x, 2, playerPos.z);
				m_particles[i].model->Scale(0.025f);
				m_particles[i].model->SetSkin("dust.png");
			}
		}

		// Always apply gravity to the particles
		float randomSpeedFactor = 1.0f + (static_cast<float>(rand()) / RAND_MAX) * speedPercentage;
		p.movementVector.y += P_GRAVITY * frametime * randomSpeedFactor;

		// Update the particle position and lifetime
		p.model->Move(p.movementVector.x * frametime, p.movementVector.y * frametime, p.movementVector.z * frametime);
		p.lifetime -= frametime;

		// Reset particle if lifetime is zero
		if (p.lifetime < 0) {
			p.isEmitted = false;
		}

		if (!p.isEmitted && speedPercentage > SPEED_DEADZONE && timeSinceLastEmit >= P_EMIT_INTERVAL * (1.0f / (1.0f + speedPercentage))) {
			float xComponent = generateRandomFloat(-10, 10) * 0.1f;
			float yComponent = generateRandomFloat(25, 50) * 0.1f;
			float zComponent = generateRandomFloat(-10, 10) * 0.1f;

			SVector3 movementVector = { xComponent, yComponent, zComponent };

			emitParticle(p, emitterPos, P_LIFETIME, movementVector);

			timeSinceLastEmit = 0.0f;
		}
	}
}
