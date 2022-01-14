#pragma once
#include "Particle.h"
#include "GameObject.h"
#include "Resource.h"
#include "Texture.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ParticleEffect.h"
#include "ParticleEffect_Velocity.h"
#include "ParticleEffect_Force.h"
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

	void CreateParticleEffect(ParticleEffectType type);
	bool isEffectActive(ParticleEffectType type);
	std::string GetNameFromEffect(ParticleEffectType type);

public:

	int maxParticles;
	float particlesPerSecond;
	bool isActive;
	bool toDelete;

	std::vector<ParticleEffect*> effects;
	std::vector<Particle> particlesBuff;
	Particle* particleReference;

	float timer;
	float currTimer;
	
private:

	char charsOfName[50];
	bool showTexMenu;
};