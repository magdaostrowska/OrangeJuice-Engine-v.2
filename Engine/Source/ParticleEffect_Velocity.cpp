#include "ParticleEffect_Velocity.h"

ParticleEffect_Velocity::ParticleEffect_Velocity() : ParticleEffect(ParticleEffectType::VELOCITY_OVER_LIFETIME)
{
	type = ParticleEffectType::VELOCITY_OVER_LIFETIME;
	minVelocity = { 0.0f,0.0f,0.0f };
	maxVelocity = { 1.0f, 1.0f, 1.0f };
}

ParticleEffect_Velocity::~ParticleEffect_Velocity()
{
}

void ParticleEffect_Velocity::Init(Particle& particle)
{
	LCG random;
	float randomVel_x = random.Float(minVelocity.x, maxVelocity.x);
	float randomVel_y = random.Float(minVelocity.y, maxVelocity.y);
	float randomVel_z = random.Float(minVelocity.z, maxVelocity.z);
	particle.velocity = { randomVel_x, randomVel_y,randomVel_z };
}

void ParticleEffect_Velocity::Update(Particle& particle, float dt)
{
}

void ParticleEffect_Velocity::OnEditor(int emitterIndex)
{
	float minVel = -1.0f;
	float maxVel = 1.0f;

	float minV[3] = { minVelocity.x, minVelocity.y, minVelocity.z };
	float maxV[3] = { maxVelocity.x, maxVelocity.y, maxVelocity.z };
	
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

		suffixLabel = "Minimum Velocity##max_vel";
		suffixLabel += emitterIndex;
		ImGui::DragFloat3(suffixLabel.c_str(), minV, 0.01f, minVel, maxVel);
		minVelocity.x = minV[0];
		minVelocity.y = minV[1];
		minVelocity.z = minV[2];

		suffixLabel = "Maximum Velocity##max_vel";
		suffixLabel += emitterIndex;
		ImGui::DragFloat3(suffixLabel.c_str(), maxV, 0.01f, minVel, maxVel);
		maxVelocity.x = maxV[0];
		maxVelocity.y = maxV[1];
		maxVelocity.z = maxV[2];

		ImGui::Unindent();
	}
}