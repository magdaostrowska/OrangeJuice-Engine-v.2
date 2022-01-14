#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(ParticleEffectType type)
{
	this->type = type;
	toDelete = false;
}

ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::Init(Particle& particle)
{
}

void ParticleEffect::Update(Particle& particle, float dt)
{
}

void ParticleEffect::OnEditor(int emitterIndex)
{
}
