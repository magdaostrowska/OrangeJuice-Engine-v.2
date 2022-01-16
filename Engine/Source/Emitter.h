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
#include "MathGeoLib/src/Algorithm/Random/LCG.h"
#include <string>

class Emitter {
public:

	Emitter(GameObject* owner);
	~Emitter();

	virtual void Emit(float dt);
	void Render();
	virtual void UpdateParticle(float dt);
	virtual void Update(float dt);

	void OnEditor(int emitterIndex);
	void SetParticlesPerSecond(float particlesPerSec);

	void CreateParticleEffect(ParticleEffectType type);
	bool isEffectActive(ParticleEffectType type);
	std::string GetNameFromEffect(ParticleEffectType type);
	ParticleEffect* GetParticleEffect(ParticleEffectType type);

	virtual bool OnLoad(JsonParsing& node);
	virtual bool OnSave(JsonParsing& node, JSON_Array* array);

protected:
	void SetParticleTexture(Particle& particle);
public:

	int maxParticles;
	float particlesPerSecond;
	bool isActive;
	bool toDelete;

	std::vector<ParticleEffect*> effects;
	std::vector<Particle*> particlesBuff;
	//std::vector<Particle*> fireworkParticlesBuff;
	Particle* particleReference;
	GameObject* own;

	float minLifeTime;
	float maxLifeTime;

	float timer;
	float currTimer;
	
private:
	
	char charsOfName[50];
	bool showTexMenu;
	LCG random;
};