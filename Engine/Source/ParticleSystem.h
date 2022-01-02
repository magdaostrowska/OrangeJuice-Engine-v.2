#pragma once
#include "Particle.h"
#include <vector>

class CameraComponent;
class ParticleEmitter;

class ParticleSystem {

public:

	ParticleSystem();
	~ParticleSystem();

	void EmitParticles();

	//virtual void Update(float fDeltaTime);
	//virtual void Render();

protected:

	void EmitParticle(Particle& particle);

private:

	typedef std::vector<Particle> ParticlesBuffer;
	std::vector<Particle> particlesBuffer;
	uint32_t particleBufferIndex = 999; // the vector of particles get resized after achieving a number of 1000 particles, so the last particle (before first) resize has index 999

	ParticleEmitter* emitter;
	ParticlesBuffer particles;
};
