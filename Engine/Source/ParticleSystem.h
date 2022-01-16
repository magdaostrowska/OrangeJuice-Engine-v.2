#pragma once
#include "Particle.h"
#include "Globals.h"
#include "Component.h"
#include "GameTimer.h"


#include "MathGeoLib/src/MathGeoLib.h"
#include <vector>

class CameraComponent;
class TransformComponent;
class Emitter;

class ParticleSystem : public Component {

public:

	ParticleSystem(GameObject* own, TransformComponent* trans, uint numParticles = 1);
	~ParticleSystem();

	void SetEmitter(Emitter* emitter);
	bool Update(float dt) override;
	void OnEditor() override;
	
	void Play();
	void Stop();

	bool OnLoad(JsonParsing& node) override;
	bool OnSave(JsonParsing& node, JSON_Array* array) override;

public:

	bool looping = false;
	float maxDuration = 0.0f;

protected:

	std::vector<Emitter*> emitters;
	bool isActive;
	GameTimer timer;
	TransformComponent* transform;
};
