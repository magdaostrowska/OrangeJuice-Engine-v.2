#include "ParticleEffect_Color.h"

ParticleEffect_Color::ParticleEffect_Color() : ParticleEffect(ParticleEffectType::COLOR_OVER_LIFETIME)
{
	type = ParticleEffectType::COLOR_OVER_LIFETIME;
}

ParticleEffect_Color::~ParticleEffect_Color()
{
}

void ParticleEffect_Color::Update(Particle& particle, float dt)
{
	if (particle.isActive)
	{
		float percentage = particle.lifeTime / 10;
		float4 color;
		particle.color = { color[0],color[1],color[2],color[3] };
	}
}

void ParticleEffect_Color::OnEditor(int emitterIndex)
{
}

bool ParticleEffect_Color::OnLoad(JsonParsing& node)
{
	return true;
}

bool ParticleEffect_Color::OnSave(JsonParsing& node, JSON_Array* array)
{
	return true;
}
