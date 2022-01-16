#pragma once
#include "ParticleEffect.h"

class ParticleEffect_Size : ParticleEffect
{
public:
	ParticleEffect_Size();
	~ParticleEffect_Size();

	void Update(Particle& particle, float dt) override;
	void OnEditor(int emitterIndex) override;

	bool OnLoad(JsonParsing& node) override;
	bool OnSave(JsonParsing& node, JSON_Array* array) override;

public:

	float2 startSize, endSize;
};