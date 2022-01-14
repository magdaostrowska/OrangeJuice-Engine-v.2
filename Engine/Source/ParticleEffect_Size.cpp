#include "ParticleEffect_Size.h"

ParticleEffect_Size::ParticleEffect_Size() : ParticleEffect(ParticleEffectType::SIZE_OVER_LIFETIME)
{
	type = ParticleEffectType::SIZE_OVER_LIFETIME;
}

ParticleEffect_Size::~ParticleEffect_Size()
{
}

void ParticleEffect_Size::Update(Particle& particle, float dt)
{
}

void ParticleEffect_Size::OnEditor(int emitterIndex)
{
}
