#include "ParticleEffect_Force.h"

ParticleEffect_Force::ParticleEffect_Force() : ParticleEffect(ParticleEffectType::ACCELERATION_OVER_LIFETIME)
{
	type = ParticleEffectType::ACCELERATION_OVER_LIFETIME;
}

ParticleEffect_Force::~ParticleEffect_Force()
{
}

void ParticleEffect_Force::Update(Particle& particle, float dt)
{
}

void ParticleEffect_Force::OnEditor(int emitterIndex)
{
}
