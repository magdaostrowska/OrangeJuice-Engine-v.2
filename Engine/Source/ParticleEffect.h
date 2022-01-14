#pragma once
#include "Particle.h"

enum class ParticleEffectType : int
{
	NO_TYPE = -1,
	COLOR_OVER_LIFETIME,
	SIZE_OVER_LIFETIME,
	VELOCITY_OVER_LIFETIME,
	ACCELERATION_OVER_LIFETIME,
};

class ParticleEffect
{
public:
	ParticleEffect(ParticleEffectType type);
	~ParticleEffect();

	virtual void Init(Particle& particle);
	virtual void Update(Particle& particle, float dt);
	virtual void OnEditor(int emitterIndex);

public:

	ParticleEffectType type;
	bool toDelete;
};