#include "Emitter.h"
#include "ResourceManager.h"
#include "Mesh.h"

Emitter::Emitter()
{
	position = { 0.0f,0.0f,0.0f };
	maxParticles = 100;
	isActive = true;
	planes.resize(maxParticles);

	particleReference = new Particle();

	for (int i = 0; i < maxParticles; i++)
	{
		planes[i] = app->scene->CreateGameObject(app->scene->smoke, true);
		planes[i]->SetName("Plane");
		planes[i]->CreateComponent(ComponentType::MESH_RENDERER);
		planes[i]->CreateComponent(ComponentType::BILLBOARD);
		planes[i]->CreateComponent(ComponentType::PARTICLE_SYSTEM);

		ResourceManager::GetInstance()->LoadResource(std::string("Assets/Resources/plane.fbx"), *planes[i]);
	}
}

Emitter::~Emitter()
{
}

void Emitter::EmitParticle(Particle& particle)
{
}

void Emitter::Emit()
{
	for (int i = 0; i < particlesBuff.size(); i++) {

		// When the particle is allocated in memory, but it's not being used at the moment
		// Reuse an exisiting particle to make the smaller complexity, which results in more optimized code 

		if (particlesBuff[i].isActive == false)
		{
			particlesBuff[i].isActive == true;
			particlesBuff[i].position = position;
			particlesBuff[i].velocity = particleReference->velocity;
			particlesBuff[i].acceleration = particleReference->acceleration;
			particlesBuff[i].rotation = particleReference->rotation;
			particlesBuff[i].size = particleReference->size;
			particlesBuff[i].color = particleReference->color;
			particlesBuff[i].lifeTime = particleReference->lifeTime;
			particlesBuff[i].timeLeft = particleReference->timeLeft;

			return;
		}
	}

	// Create new particle
	currTimer -= 0.5f;
	if (currTimer <= 0.0f) {
		if (particlesBuff.size() < maxParticles) {
			Particle particle = new Particle(particleReference);
			particlesBuff.push_back(particle);
		}
		currTimer = timer;
	}
	
}

void Emitter::Render()
{
	for (int i = 0; i < particlesBuff.size(); i++) {

		BillboardParticle* planeBillboard = (BillboardParticle*)planes[i]->GetComponent(ComponentType::BILLBOARD);
		if (planeBillboard != nullptr)
		{
			// TODO - RotateToFaceCamera() method
		}

		TransformComponent* planeTransform = (TransformComponent*)planes[i]->GetComponent(ComponentType::TRANSFORM);
		if (planeTransform != nullptr)
		{
			planeTransform->SetTransform(particlesBuff[i].position, Quat::identity, particlesBuff[i].size);
		}
	}
}

void Emitter::UpdateParticle(float dt)
{
	for (int i = 0; i < particlesBuff.size(); i++) {
		particlesBuff[i].position += particlesBuff[i].velocity;
	}
}

void Emitter::Update(float dt)
{
	UpdateParticle(dt);
	Render();
	Emit();
}