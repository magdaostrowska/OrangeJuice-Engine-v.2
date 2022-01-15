#pragma once
#include "Particle.h"
#include "GameObject.h"
#include "Resource.h"
#include "Texture.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ParticleEffect.h"
#include "ParticleEffect_Velocity.h"
#include "ParticleEffect_Acceleration.h"
#include "ParticleEffect_Size.h"
#include "MathGeoLib/src/Geometry/Frustum.h"
#include <string>

class Emitter {
public:

	Emitter(GameObject* owner);
	~Emitter();

	void Emit(float dt);
	void Render();
	void UpdateParticle(float dt);
	void Update(float dt);

	void OnEditor(int emitterIndex);
	void SetParticlesPerSecond(float particlesPerSec);

	void CreateParticleEffect(ParticleEffectType type);
	bool isEffectActive(ParticleEffectType type);
	std::string GetNameFromEffect(ParticleEffectType type);
	ParticleEffect* GetParticleEffect(ParticleEffectType type);

private:
	void SetParticleTexture(Particle& particle);
public:

	int maxParticles;
	float particlesPerSecond;
	bool isActive;
	bool toDelete;

	std::vector<ParticleEffect*> effects;
	std::vector<Particle*> particlesBuff;
	Particle* particleReference;
	GameObject* own;

	float3 minVelocity;
	float3 maxVelocity;

	float timer;
	float currTimer;
	
private:

	char charsOfName[50];
	bool showTexMenu;
};