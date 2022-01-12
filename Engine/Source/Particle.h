#pragma once
#include "glmath.h"
#include "MathGeoLib/src/Geometry/Frustum.h"

class Particle {

public:

	// This constructor is made to create the particle reference only
	Particle() {
		lifeTime = 10.0f;
		rotation = { 0.0f,0.0f,0.0f };
		acceleration = { 0.0f,0.0f,0.0f };
		size = { 1.0f,1.0f,1.0f };
		velocity = { 0.0f,0.01f,0.0f };
		position = { 0.0f,0.0f,0.0f };
		color = { 0, 0, 0 };
		isActive = true;
	}

	// This constructor should be used by default
	Particle(Particle* particleReference) 
	{
		lifeTime = particleReference->lifeTime;
		rotation = particleReference->rotation;
		acceleration = particleReference->acceleration;
		size = particleReference->size;
		velocity = particleReference->velocity;
		position = particleReference->position;
		color = particleReference->color;
		isActive = particleReference->isActive;
	}

public:

	float lifeTime;
	float3 rotation, acceleration;
	float3 size; // float startSize, endSize
	float3 velocity, position, direction;
	Vec4 color;
	//Vec3 startColor, endColor;
	//Vec4 color4, startColor4, endColor4;
	bool isActive;
};
