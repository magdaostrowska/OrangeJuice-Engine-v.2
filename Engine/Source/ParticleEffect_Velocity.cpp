#include "ParticleEffect_Velocity.h"

ParticleEffect_Velocity::ParticleEffect_Velocity() : ParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME)
{
	type = ParticleEffectType::VELOCITY_OVER_LIFETIME;
	velocity = float3(0,0,0);
}

ParticleEffect_Velocity::~ParticleEffect_Velocity()
{
}

void ParticleEffect_Velocity::Update(Particle& particle, float dt)
{
	particle.position.x += velocity[0] * dt;
	particle.position.y += velocity[1] * dt;
	particle.position.z += velocity[2] * dt;
}

void ParticleEffect_Velocity::OnEditor(int emitterIndex)
{
	float vel[3] = { velocity[0], velocity[1], velocity[2] };

	std::string suffixLabel = "Velocity Over Lifetime Effect##";
	suffixLabel += emitterIndex;
	if (ImGui::CollapsingHeader(suffixLabel.c_str(), ImGuiTreeNodeFlags_Bullet))
	{
		suffixLabel = "Delete Velocity Over Lifetime Effect##";
		suffixLabel += emitterIndex;
		if (ImGui::Button(suffixLabel.c_str()))
			this->toDelete = true;

		ImGui::Spacing();
		ImGui::Indent();

		suffixLabel = "Velocity##vel";
		suffixLabel += emitterIndex;
		ImGui::DragFloat3(suffixLabel.c_str(), vel, 0.1f);
		velocity[0] = vel[0];
		velocity[1] = vel[1];
		velocity[2] = vel[2];

		ImGui::Unindent();
	}
}
