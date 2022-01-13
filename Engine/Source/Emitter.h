#pragma once
#include "Particle.h"
#include "GameObject.h"
#include "Resource.h"
#include "Application.h"
#include "ModuleScene.h"
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
	int maxParticles;
	float particlesPerSecond;
	bool isActive;
	bool toDelete;

	//std::vector<GameObject*> planes;
	std::vector<Particle> particlesBuff;
	Particle* particleReference;

	float timer;
	float currTimer;
	
private:

	char charsOfName[50];
	std::shared_ptr<Texture> tex;
};