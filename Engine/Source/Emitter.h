#pragma once
#include "MathGeoLib/src/Geometry/Frustum.h"
#include "Particle.h"

class Emitter {

public:
	Emitter();
	~Emitter();

	virtual void EmitParticle(Particle& particle);

	float3 position;
};