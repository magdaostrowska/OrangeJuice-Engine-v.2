#pragma once
#include "ParticleEffect.h"

class ParticleEffect_Velocity : ParticleEffect
{
public:
	ParticleEffect_Velocity();
	~ParticleEffect_Velocity();

	void Init(Particle& particle) override;
	void Update(Particle& particle, float dt) override;
	void OnEditor(int emitterIndex) override;

public:

	float3 velocity;
};