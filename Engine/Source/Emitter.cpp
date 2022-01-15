#include "Emitter.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "TextureImporter.h"

Emitter::Emitter()
{
	maxParticles = 10;
	particlesPerSecond = 1;
	isActive = true;

	particleReference = new Particle();
	effects.resize(5);

	timer = 1.0f/particlesPerSecond;
	currTimer = timer;

	showTexMenu = false;

	minVelocity = {0.0f, 0.0f, 0.0f};
	maxVelocity = { 1.0f, 1.0f, 1.0f };
}

Emitter::~Emitter()
{
}

void Emitter::Emit(float dt)
{
	currTimer -= dt;
	if (currTimer <= 0.0f) {
		
		for (int i = 0; i < particlesBuff.size(); i++) {
			// When the particle is allocated in memory, but it's not being used at the moment
			// Reuse an exisiting particle to make the smaller complexity, which results in more optimized code 

			if (particlesBuff[i]->isActive == false)
			{
				particlesBuff[i]->isActive = true;
				particlesBuff[i]->position = { 0,0,0 }; //particleReference->position;
				particlesBuff[i]->velocity = { 0,0,0 }; //particleReference->velocity;
				particlesBuff[i]->acceleration = { 0,0,0 }; //particleReference->acceleration;
				particlesBuff[i]->rotation = particleReference->rotation;
				particlesBuff[i]->size = particleReference->size;
				particlesBuff[i]->color = particleReference->color;
				particlesBuff[i]->lifeTime = particleReference->lifeTime;

				SetParticleTexture(*particlesBuff[i]);

				for (int j = 0; j < effects.size(); j++)
				{
					if (effects[j] != nullptr)
					{
						effects[j]->Init(*particlesBuff[i]);
					}
				}
				return;
			}
		}

		if (particlesBuff.size() < maxParticles) {
			// Create new particle
			Particle* particle = new Particle(particleReference);
			particlesBuff.push_back(particle);
			SetParticleTexture(*particle);
		}
		currTimer = timer;
	}
}

void Emitter::Render()
{
	for (int i = 0; i < particlesBuff.size(); i++) {

		if (particlesBuff[i]->isActive == true)
		{
			BillboardParticle* planeBillboard = (BillboardParticle*)particlesBuff[i]->plane->GetComponent(ComponentType::BILLBOARD);
			if (planeBillboard != nullptr)
			{
				// TODO: RotateToFaceCamera() method
			}

			TransformComponent* planeTransform = (TransformComponent*)particlesBuff[i]->plane->GetComponent(ComponentType::TRANSFORM);
			if (planeTransform != nullptr)
			{
				planeTransform->SetTransform(particlesBuff[i]->position, Quat::FromEulerXYZ(particlesBuff[i]->rotation.x, particlesBuff[i]->rotation.y, particlesBuff[i]->rotation.z), particlesBuff[i]->size);
			}

			MaterialComponent* planeMaterial = (MaterialComponent*)particlesBuff[i]->plane->GetComponent(ComponentType::MATERIAL);
			if (planeMaterial != nullptr)
			{
				//planeMaterial
			}

			MeshComponent* planeMesh = (MeshComponent*)particlesBuff[i]->plane->GetComponent(ComponentType::MESH_RENDERER);
			if (planeMesh != nullptr)
			{
				planeMesh->colorNormal = particlesBuff[i]->color;
			}
		}
	}
}

void Emitter::UpdateParticle(float dt)
{
	for (int i = 0; i < particlesBuff.size(); i++) {
		
		if (particlesBuff[i]->isActive == true)
		{
			for (int j = 0; j < effects.size(); j++)
			{
				if (effects[j] != nullptr && isEffectActive(effects[j]->type))
				{
					effects[j]->Update(*particlesBuff[i], dt);
				}
			}

			particlesBuff[i]->lifeTime -= dt;
			particlesBuff[i]->velocity += particlesBuff[i]->acceleration;// * dt;
			particlesBuff[i]->position += particlesBuff[i]->velocity;
		}

		if (particlesBuff[i]->lifeTime <= 0)
			particlesBuff[i]->isActive = false;
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
		guiName = "Delete Emitter" + suffixLabel;
		if (ImGui::Button(guiName.c_str()))
		{
			toDelete = true;
		}

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Indent();

		guiName = "Particle Lifetime" + suffixLabel;
		if (ImGui::DragFloat(guiName.c_str(), &particleReference->lifeTime)){}

		guiName = "Particles per Second" + suffixLabel;
		if (ImGui::DragFloat(guiName.c_str(), &particlesPerSecond))
			SetParticlesPerSecond(particlesPerSecond);

		guiName = "Max Particles" + suffixLabel;
		if (ImGui::DragInt(guiName.c_str(), &maxParticles)){}

		float size[2] = { particleReference->size.x, particleReference->size.y };

		guiName = "Size" + suffixLabel;
		if (ImGui::DragFloat2(guiName.c_str(), size))
		{
			particleReference->size.x = size[0];
			particleReference->size.y = size[1];
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

		ImGui::Indent();

		//TODO: Texture part
		ImGui::Text("Texture");

		if (particleReference->tex != nullptr)
		{
			
			if (ImGui::ImageButton((ImTextureID)particleReference->tex->id, ImVec2(64, 64), ImVec2(0, 1), ImVec2(1, 0)))
			{

			}

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
				ImGui::Text("Click on the image to erase it");
				ImGui::PopStyleColor();
				ImGui::EndTooltip();
			}
		}
		else
		{
			ImGui::Image((ImTextureID)0, ImVec2(64, 64), ImVec2(0, 1), ImVec2(1, 0));
		}

		for (int i = (int)ParticleEffectType::NO_TYPE + 1; i <= (int)ParticleEffectType::ACCELERATION_OVER_LIFETIME; i++)
		{
			if (isEffectActive((ParticleEffectType)i))
			{
				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();
				ImGui::Spacing();

				effects[(int)(ParticleEffectType)i]->OnEditor(emitterIndex);
			}
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();

		guiName = "Add Effect##PaShapeEf";
		guiName += emitterIndex;

		std::string textNameDisplay = "NEW EFFECT";

		textNameDisplay += "##PaShapeEf";
		textNameDisplay += emitterIndex;
		if (ImGui::BeginCombo(guiName.c_str(), textNameDisplay.c_str()))
		{
			for (int j = (int)ParticleEffectType::NO_TYPE + 1; j <= (int)ParticleEffectType::ACCELERATION_OVER_LIFETIME; j++)
			{
				guiName = (GetNameFromEffect((ParticleEffectType)j)) + suffixLabel;

				int index = isEffectActive((ParticleEffectType)j);
				if (isEffectActive((ParticleEffectType)j) == false)
				{
					//if the effect hasnt been created
					if (ImGui::Selectable(guiName.c_str()))
					{
						CreateParticleEffect((ParticleEffectType)j);
					}
				}
			}
			ImGui::EndCombo();
		}
	}
}

void Emitter::SetParticlesPerSecond(float particlesPerSec)
{
	particlesPerSecond = particlesPerSec;
	//timer = 1.0f / particlesPerSecond;
}

void Emitter::CreateParticleEffect(ParticleEffectType type)
{
	ParticleEffect* effect = nullptr;

	switch (type)
	{
	case ParticleEffectType::NO_TYPE:
		effects[(int)ParticleEffectType::NO_TYPE] = effect;
		break;
	case ParticleEffectType::COLOR_OVER_LIFETIME:
		effects[(int)ParticleEffectType::COLOR_OVER_LIFETIME] = effect;
		break;
	case ParticleEffectType::SIZE_OVER_LIFETIME:
		effect = (ParticleEffect*)new ParticleEffect_Size();
		effects[(int)ParticleEffectType::SIZE_OVER_LIFETIME] = effect;
		break;
	case ParticleEffectType::VELOCITY_OVER_LIFETIME:
		effect = (ParticleEffect*)new ParticleEffect_Velocity();
		effects[(int)ParticleEffectType::VELOCITY_OVER_LIFETIME] = effect;
		break;
	case ParticleEffectType::ACCELERATION_OVER_LIFETIME:
		effect = (ParticleEffect*)new ParticleEffect_Acceleration();
		effects[(int)ParticleEffectType::ACCELERATION_OVER_LIFETIME] = effect;
		break;
	default:
		break;
	}
}

bool Emitter::isEffectActive(ParticleEffectType type)
{
	for (int i = 0; i < effects.size(); ++i)
	{
		if (effects[i] != nullptr && effects[i]->type == type)
		{
			return true;
		}
	}
	return false;
}

std::string Emitter::GetNameFromEffect(ParticleEffectType type)
{
	switch (type)
	{
	case ParticleEffectType::NO_TYPE:
		return "No Type";
		break;
	case ParticleEffectType::COLOR_OVER_LIFETIME:
		return "Color Effect";
		break;
	case ParticleEffectType::SIZE_OVER_LIFETIME:
		return "Size Effect";
		break;
	case ParticleEffectType::VELOCITY_OVER_LIFETIME:
		return "Velocity Effect";
		break;
	case ParticleEffectType::ACCELERATION_OVER_LIFETIME:
		return "Acceleration Effect";
		break;
	default:
		break;
	}
}

void Emitter::SetParticleTexture(Particle& particle)
{
	MaterialComponent* matRef = (MaterialComponent*)particleReference->plane->GetComponent(ComponentType::MATERIAL);
	if (matRef != nullptr) {
		if (particle.plane->GetComponent(ComponentType::MATERIAL) == nullptr) {
			particle.plane->CreateComponent(ComponentType::MATERIAL);
			MaterialComponent* mat = (MaterialComponent*)particle.plane->GetComponent(ComponentType::MATERIAL);
			mat->diff = matRef->diff;
			mat->checker = matRef->checker;
		}
		else {
			MaterialComponent* mat = (MaterialComponent*)particle.plane->GetComponent(ComponentType::MATERIAL);
			mat->diff = matRef->diff;
			mat->checker = matRef->checker;
		}
	}
}
