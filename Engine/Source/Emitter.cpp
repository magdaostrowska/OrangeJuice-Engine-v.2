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
	planeTransform = (TransformComponent*)plane->GetComponent(ComponentType::TRANSFORM);
	//planeMesh = plane->GetComponent(ComponentType::MESH_RENDERER);
	/*std::string meshName;
	std::string assetsPath("Assets/Resources/plane.fbx");
	uint planeUID = ResourceManager::GetInstance()->CreateResource(ResourceType::MESH, assetsPath, meshName);

	//planeMesh = ResourceManager::GetInstance()->GetResource(planeUID);
	planeMesh  = std::static_pointer_cast<Mesh>(ResourceManager::GetInstance()->GetResource(planeUID));
	MeshComponent* mesh = (MeshComponent*)plane->GetComponent(ComponentType::MESH_RENDERER);
	mesh->SetMesh(planeMesh);*/
	//planeMesh->Reimport(parameters);
	
	//planeMesh->shared_from_this().

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
	if (particlesBuff.size() < 200) {
		Particle particle = new Particle(particleReference);
		particlesBuff.push_back(particle);
	}
}

void Emitter::Render()
{
	for (int i = 0; i < particlesBuff.size(); i++) {
		planeTransform->SetTransform(particlesBuff[i].position, Quat::identity, particlesBuff[i].size);
		//plane->Draw();
	}
	/*if (particlesBuff.size() > 0) {
		DEBUG_LOG("Particle 0 posY: ", particlesBuff[0].position.y);
		planeTransform->SetTransform(particlesBuff[0].position, Quat::identity, particlesBuff[0].size);
		plane->Draw();
	}*/	
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

	currTimer -= dt;
	if (currTimer <= 0.0f) {
		Emit();
		currTimer = timer;
	}	
}