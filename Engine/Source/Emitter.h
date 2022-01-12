#pragma once
#include "MathGeoLib/src/Geometry/Frustum.h"
#include "Particle.h"
#include "GameObject.h"
#include "Resource.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Texture.h"
#include "MathGeoLib/src/Geometry/Frustum.h"
#include <string>

class Emitter {
public:

	Emitter();
	~Emitter();

	virtual void EmitParticle(Particle& particle);

	void Emit(float dt);
	void Render();
	void UpdateParticle(float dt);
	void Update(float dt);

	void OnEditor(int emitterIndex);
	void SetParticlesPerSecond(float particlesPerSec);

public:

	float3 position;
	bool isActive;

	std::vector<GameObject*> planes;
	std::vector<Particle> particlesBuff;
	Particle* particleReference;

	int maxParticles;
	float particlesPerSecond;

	float timer;
	float currTimer;

	bool toDelelte;

private:

	char charsOfName[50];
	Texture* texture;
};