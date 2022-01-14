#pragma once
#include "ParticleEffect.h"

class ParticleEffect_Force : ParticleEffect
{
public:
	ParticleEffect_Force();
	~ParticleEffect_Force();

	void Update(Particle& particle, float dt) override;
	void OnEditor(int emitterIndex) override;

};