#pragma once
#include "MathGeoLib/src/Geometry/Frustum.h"
#include "Particle.h"

class Emitter {

public:
	Emitter();
	~Emitter();

	virtual void EmitParticle(Particle& particle);

	void Emit();
	void Render();
	void UpdateParticle(float dt);
	void Update(float dt);

public:

	float3 position;
	bool isActive;

	std::vector<Particle> particlesBuff;
	Particle* particleReference;
};