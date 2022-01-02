#pragma once
#include "glmath.h"
#include "MathGeoLib/src/Geometry/Frustum.h"

class Particle {

public:

	float age, lifeTime, timeLeft;
	float size, startSize, endSize;
	float rotation, acceleration;
	float3 velocity, position;
	Vec3 color, startColor, endColor;
	Vec4 color4, startColor4, endColor4;
	bool isActive;

};
