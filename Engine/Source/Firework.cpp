#include "Firework.h"
#include "ParticleSystem.h"

Firework::Firework(GameObject* owner) : Emitter(owner)
{
	isActive = true;
	particlesBuff.resize(0);
	own = owner;
	maxParticles = 100; 
	particlesBuff.resize(maxParticles);
	for (int i = 0; i < particlesBuff.size(); i++) {
		// Create new particle
		Particle* particle = new Particle(particleReference, own);
		particlesBuff[i] = particle;
		SetParticleTexture(*particle);

		particle->velocity = { 0.0f, 1.0f, 0.0f };
	}

	particlesPerSecond = 20;
	timer = 1.0f / particlesPerSecond;
	currTimer = timer;

	particlesRandomized.resize(maxParticles);
	for (int i = 0; i < maxParticles; i++) {
		particlesRandomized.push_back(false);
	}

	CreateParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME);
	ParticleEffect_Velocity* velocityEffect = (ParticleEffect_Velocity*)GetParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME);
	velocityEffect->minVelocity = velocityEffect->maxVelocity = { 0.0f, 1.0f, 0.0f };
	limitY = 20.0f;
	particleReference->size = { 0.5f,  0.5f ,  0.5f };
}

void Firework::Update(float dt)
{
	for (int i = 0; i < particlesBuff.size(); i++) {

		if (particlesBuff[i]->isActive == true) {
			
			if (particlesBuff[i]->position.y >= limitY && particlesRandomized[i] == false) {
				float3 minVelocity = { -0.5f, 0.0f, -0.5f };
				float3 maxVelocity = { 0.5f, 0.0f, 0.5f };
				LCG random;
				float randomVel_x = random.Float(minVelocity.x, maxVelocity.x);
				float randomVel_y = random.Float(minVelocity.y, maxVelocity.y);
				float randomVel_z = random.Float(minVelocity.z, maxVelocity.z);
				particlesBuff[i]->velocity = float3(randomVel_x, randomVel_y,randomVel_z);

				CreateParticleEffect(ParticleEffectType::ACCELERATION_OVER_LIFETIME);
				ParticleEffect_Acceleration* accelerationEffect = (ParticleEffect_Acceleration*)GetParticleEffect(ParticleEffectType::ACCELERATION_OVER_LIFETIME);
				accelerationEffect->acceleration = { 0.0f, -0.001f, 0.0f };
				accelerationEffect->hasGravity = false;

				particlesRandomized[i] = true;
			}
		}
	}

	UpdateParticle(dt);
	Render();
	Emit(dt);
}

void Firework::UpdateParticle(float dt)
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
			particlesBuff[i]->velocity += particlesBuff[i]->acceleration * dt;// * dt;
			particlesBuff[i]->position += particlesBuff[i]->velocity;
		}

		if (particlesBuff[i]->lifeTime <= 0) {
			particlesBuff[i]->isActive = false;
			/*if (selected && selected->GetComponent(ComponentType::CAMERA) == nullptr)
			{
				for (std::vector<GameObject*>::iterator i = selectedParent->GetChilds().begin(); i != selectedParent->GetChilds().end(); ++i)
				{
					if (selected == (*i))
					{
						selectedParent->GetChilds().erase(i);
						if (selected == app->scene->GetRecalculateGO()) app->scene->RecalculateAABB(nullptr);
						RELEASE(selected);
						app->scene->ResetQuadtree();
						break;
					}
				}
			}*/
		}			
	}
}

void Firework::Emit(float dt)
{
	currTimer -= dt;
	if (currTimer <= 0.0f) {
		currTimer = timer;
		for (int i = 0; i < particlesBuff.size(); i++) {
			
			if (particlesRandomized[i] == false) {
				TransformComponent* transform = (TransformComponent*)own->GetComponent(ComponentType::TRANSFORM);
				if (transform != nullptr)
				{
					if (particlesBuff[i]->isActive == false)
					{
						particlesBuff[i]->isActive = true;
						particlesBuff[i]->position = transform->position;
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
			}
		}
		bool finished = false;
		for (int i = 0; i < particlesRandomized.size(); i++) {
			if (particlesRandomized[i] == true) finished = true;
		}
		if (finished == true)
			KillParticles(); //TODO: Add a timer to kill them later
	}
}

bool Firework::OnLoad(JsonParsing& node)
{
	limitY = node.GetJsonBool("LimitY");
	return true;
}

bool Firework::OnSave(JsonParsing& node, JSON_Array* array)
{
	JsonParsing file = JsonParsing();
	file.SetNewJsonNumber(file.ValueToObject(file.GetRootValue()), "LimitY", limitY);
	node.SetValueToArray(array, file.GetRootValue());
	return true;
}

void Firework::KillParticles()
{
	for (int i = 0; i < particlesBuff.size(); i++) {
		if(particlesBuff[i]->isActive == false){
			TransformComponent* trans = (TransformComponent*)particlesBuff[i]->plane->GetComponent(ComponentType::TRANSFORM);
			trans->SetTransform({ -9999999, -9999999, -9999999 }, Quat::identity, { 0.0, 0.0, 0.0 });
		}
	}
}
