#include "Emitter.h"
#include "ResourceManager.h"
#include "Mesh.h"

Emitter::Emitter()
{
	position = { 0.0f,0.0f,0.0f };
	maxParticles = 100;
	particlesPerSecond = 3;
	isActive = true;
	planes.resize(maxParticles);

	particleReference = new Particle();

	timer = 1/particlesPerSecond;
	currTimer = timer;

	texture = nullptr;

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

void Emitter::Emit(float dt)
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

			return;
		}
	}

	// Create new particle
	currTimer -= dt;
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
		
		particlesBuff[i].lifeTime -= dt;
		particlesBuff[i].position += particlesBuff[i].velocity;
		particlesBuff[i].velocity += particlesBuff[i].acceleration;	

		if (particlesBuff[i].lifeTime <= 0)
			particlesBuff[i].isActive = false;
	}
}

void Emitter::Update(float dt)
{
	UpdateParticle(dt);
	Render();
	Emit(dt);
}

void Emitter::OnEditor(int emitterIndex)
{
	std::string suffixLabel = "##";
	suffixLabel += emitterIndex;
	std::string guiName = "Emitter " + suffixLabel;

	if (ImGui::CollapsingHeader(guiName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		strcpy(charsOfName, guiName.c_str());
		guiName = suffixLabel + "Name";
		guiName = "Delelte Emitter" + suffixLabel;
		if (ImGui::Button(guiName.c_str()))
		{
			toDelelte = true;
		}

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Indent();

		guiName = "Particle Lifetime" + suffixLabel;
		if (ImGui::DragFloat(guiName.c_str(), &particleReference->lifeTime)){}
			//CalculatePoolSize();

		guiName = "Particles per Second" + suffixLabel;
		if (ImGui::DragFloat(guiName.c_str(), &particlesPerSecond))
			SetParticlesPerSecond(particlesPerSecond);

		float size[3] = { particleReference->size.x, particleReference->size.y, particleReference->size.z };

		guiName = "Size" + suffixLabel;
		if (ImGui::DragFloat(guiName.c_str(), size))
		{
			particleReference->size.x = size[0];
			particleReference->size.y = size[1];
			particleReference->size.z = size[2];
		}

		float color[4] = { particleReference->color.r, particleReference->color.g, particleReference->color.b, particleReference->color.a };

		guiName = "Color (RGBA)" + suffixLabel;
		if (ImGui::ColorPicker3(guiName.c_str(), color))
		{
			particleReference->color.r = color[0];
			particleReference->color.g = color[1];
			particleReference->color.b = color[2];
			particleReference->color.a = color[3];
		}

		//TODO: Texture part

	}
}

void Emitter::SetParticlesPerSecond(float particlesPerSec)
{
	particlesPerSecond = particlesPerSec;
}