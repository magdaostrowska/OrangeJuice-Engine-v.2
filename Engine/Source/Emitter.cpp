#include "Emitter.h"
#include "ResourceManager.h"
#include "Mesh.h"

Emitter::Emitter()
{
	position = { 0.0f,0.0f,0.0f };
	isActive = true;

	plane = app->scene->CreateGameObject(nullptr, true);
	plane->SetName("Plane");
	plane->CreateComponent(ComponentType::MESH_RENDERER);
	plane->CreateComponent(ComponentType::BILLBOARD);
	//planeMesh = std::shared_ptr<Mesh>((Mesh*)(plane->GetComponent(ComponentType::MESH_RENDERER)));
	//Mesh *m = (Mesh*)(plane->GetComponent(ComponentType::MESH_RENDERER));
	//std::shared_ptr<Mesh> planeMesh = std::static_pointer_cast<Mesh>(ResourceManager::GetInstance()->LoadResource(std::string("Assets/Resources/plane.fbx")));

	//if (planeMesh != nullptr) 
	// {
		//planeMesh =
		//planeMesh = std::static_pointer_cast<Mesh>(ResourceManager::GetInstance()->LoadResource(std::string("Assets/Resources/plane.fbx")));
	//}
		// = LoadResource(std::string("Assets/Resources/plane.fbx"));

	particleReference = new Particle();
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
	Particle particle = new Particle(particleReference);
	particlesBuff.push_back(particle);
}

void Emitter::Render()
{

}

void Emitter::UpdateParticle(float dt)
{
}

void Emitter::Update(float dt)
{
	UpdateParticle(dt);
	Render();
	Emit();
}