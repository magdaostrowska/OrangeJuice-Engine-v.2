#pragma once
#include "ParticleEffect.h"

class ParticleEffect_Color : ParticleEffect
{
public:
	ParticleEffect_Color();
	~ParticleEffect_Color();

	void Update(Particle& particle, float dt) override;
	void OnEditor(int emitterIndex) override;

};