#include "Firework.h"

Firework::Firework(GameObject* owner) : Emitter(owner)
{
	particlesBuff.resize(0);
	own = owner;
	directionChanged = false;
	CreateParticleEffect(ParticleEffectType::ACCELERATION_OVER_LIFETIME);
	ParticleEffect_Acceleration* accelerationEffect = (ParticleEffect_Acceleration*)GetParticleEffect(ParticleEffectType::ACCELERATION_OVER_LIFETIME);
	accelerationEffect->acceleration = { 0.0f, 0.00f, 0.0f };
	accelerationEffect->hasGravity = false;

	CreateParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME);
	ParticleEffect_Velocity* velocityEffect = (ParticleEffect_Velocity*)GetParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME);
	velocityEffect->minVelocity = velocityEffect->maxVelocity = { 0.0f, 1.0f, 0.0f };
	limitY = 10.0f;
	particleReference->size = { 0.1f,  0.1f ,  0.1f };
}

void Firework::Update(float dt)
{
	for (int i = 0; i < particlesBuff.size(); i++) {

		if (particlesBuff[i]->isActive == true) {
			if (particlesBuff[i]->position.y - limitY > 0.1f) {
				ParticleEffect_Velocity* velocityEffect = (ParticleEffect_Velocity*)GetParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME);
				velocityEffect->minVelocity = { -0.5f, 0.2f, -0.5f };
				velocityEffect->maxVelocity = { 0.5f, 0.2f, 0.5f };
				LCG random;
				float randomVel_x = random.Float(minVelocity.x, maxVelocity.x);
				float randomVel_y = random.Float(minVelocity.y, maxVelocity.y);
				float randomVel_z = random.Float(minVelocity.z, maxVelocity.z);
				particlesBuff[i]->velocity = float3(randomVel_x, randomVel_y,randomVel_z );
				directionChanged = true;
			}
		}
	}

	UpdateParticle(dt);
	Render();
	Emit(dt);
}

void Firework::Emit(float dt)
{
	currTimer -= dt;
	if (currTimer <= 0.0f) {

		for (int i = 0; i < particlesBuff.size(); i++) {
			// When the particle is allocated in memory, but it's not being used at the moment
			// Reuse an exisiting particle to make the smaller complexity, which results in more optimized code 

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
					particlesBuff[i]->lifeTime = 1.0f;

					SetParticleTexture(*particlesBuff[i]);

					particlesBuff[i]->velocity = { 0.0f, 0.2f, 0.0f };
					/*for (int j = 0; j < effects.size(); j++)
					{
						if (effects[j] != nullptr)
						{
							effects[j]->Init(*particlesBuff[i]);
						}
					}*/
					return;
				}
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
