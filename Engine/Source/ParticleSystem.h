#pragma once
#include "Particle.h"
#include "Globals.h"
#include "Component.h"

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
	virtual void Render();
	bool Update(float dt) override;
	void OnEditor() override;

	void Resize(uint particlesNumber);

public:

	// A vertex for the particle
	struct Vertex
	{
		Vertex(): 
			pos(0.0f), 
			diff(0), 
			tex(0)
		{}

		float3   pos;      // Vertex position
		Vec3   diff;  // Diffuse color
		Vec2   tex;     // Texture coordinate
	};
	typedef std::vector<Vertex> VertexBuffer;

protected:

	void EmitParticles();
	void BuildVertex();

private:

	std::vector<Particle> particlesBuffer;
	std::vector<Emitter*> emitters;

	//Particle* particleReference;

	VertexBuffer vertexBuffer;
	uint textureId;

	TransformComponent* transform;
};
