#include "ParticleSystem.h"
#include "Emitter.h"

#include <cassert>
#include "Globals.h"

ParticleSystem::ParticleSystem()
{
	particlesBuffer.resize(1000);
}

ParticleSystem::~ParticleSystem()
{
	particlesBuffer.clear();
}

void ParticleSystem::EmitParticles()
{
    if (emitter == NULL)
    {
        //RandomizeParticles();
    }
    else
    {
        for (uint i = 0; i < particles.size(); ++i)
        {
            EmitParticle(particles[i]);
        }
    }
}

void ParticleSystem::EmitParticle(Particle& particle)
{
	assert(emitter != NULL);
	
}
