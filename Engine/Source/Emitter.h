#pragma once
#include "MathGeoLib/src/Geometry/Frustum.h"
#include "Particle.h"
#include "GameObject.h"
#include "Resource.h"
#include "Application.h"
#include "ModuleScene.h"
#include <string>

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

	GameObject* plane;
	TransformComponent* planeTransform;
	//std::shared_ptr<Mesh> planeMesh;
	std::shared_ptr<Mesh> planeMesh;

	std::vector<Particle> particlesBuff;
	Particle* particleReference;

	float timer = 10.0f;
	float currTimer = 10.0f;
};