#include "ParticleEffect_Velocity.h"

ParticleEffect_Velocity::ParticleEffect_Velocity() : ParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME)
{
	type = ParticleEffectType::VELOCITY_OVER_LIFETIME;
	velocity = float3( 0.0f,0.0f,0.0f );
}

ParticleEffect_Velocity::~ParticleEffect_Velocity()
{
}

void ParticleEffect_Velocity::Init(Particle& particle)
{
	particle.velocity = { velocity.x,velocity.y,velocity.z };
}

void ParticleEffect_Velocity::Update(Particle& particle, float dt)
{
	////Add velocity value from inspector into particle's velocity
	//particle.velocity.x = velocity.x;
	//particle.velocity.y = velocity.y;
	//particle.velocity.z = velocity.z;

	////Update position based on particle's velocity
	//particle.position.x += particle.velocity.x * dt;
	//particle.position.y += particle.velocity.y * dt;
	//particle.position.z += particle.velocity.z * dt;
}

void ParticleEffect_Velocity::OnEditor(int emitterIndex)
{
	float vel[3] = { velocity.x, velocity.y, velocity.z };
	float minVel = -1.0f;
	float maxVel = 1.0f;

	std::string suffixLabel = "Velocity Over Lifetime Effect##";
	suffixLabel += emitterIndex;
	if (ImGui::CollapsingHeader(suffixLabel.c_str(), ImGuiTreeNodeFlags_Bullet))
	{
		suffixLabel = "Delete Effect##";
		suffixLabel += emitterIndex;
		if (ImGui::Button(suffixLabel.c_str()))
			this->toDelete = true;

		ImGui::Spacing();
		ImGui::Indent();

		suffixLabel = "Velocity##vel";
		suffixLabel += emitterIndex;
		ImGui::DragFloat3(suffixLabel.c_str(), vel, 0.01f, minVel, maxVel);
		velocity = { vel[0],vel[1],vel[2] };

		ImGui::Unindent();
	}
}