#include "Firework.h"
#include "ParticleSystem.h"

Firework::Firework(GameObject* owner) : Emitter(owner)
{
	isActive = true;
	particlesBuff.resize(0);
	own = owner;
	maxParticles = 100;
	particlesRandomized.resize(maxParticles);
	for (int i = 0; i < maxParticles; i++) {
		particlesRandomized[i] = false;
	}
	//particleReference->lifeTime = 15.0f;

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
				ParticleEffect_Velocity* velocityEffect = (ParticleEffect_Velocity*)GetParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME);
				velocityEffect->minVelocity = { -0.5f, -0.2f, -0.5f };
				velocityEffect->maxVelocity = { 0.0f, 0.2f, 0.5f };
				LCG random;
				float randomVel_x = random.Float(minVelocity.x, maxVelocity.x);
				float randomVel_y = random.Float(minVelocity.y, maxVelocity.y);
				float randomVel_z = random.Float(minVelocity.z, maxVelocity.z);
				particlesBuff[i]->velocity = float3(randomVel_x, randomVel_y,randomVel_z );

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
		if (particlesBuff.size() < maxParticles) {
			// Create new particle
			Particle* particle = new Particle(particleReference, own);
			particlesBuff.push_back(particle);
			SetParticleTexture(*particle);

			for (int j = 0; j < effects.size(); j++)
			{
				if (effects[j] != nullptr)
				{
					effects[j]->Init(*particle);
				}
			}
		}
		else {
			/*ParticleSystem* particleSystem = (ParticleSystem*)own->GetComponent(ComponentType::PARTICLE_SYSTEM);
			particleSystem->looping = false;
			particleSystem->Stop();
			particleSystem->Play();*/
		}
		currTimer = timer;
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
