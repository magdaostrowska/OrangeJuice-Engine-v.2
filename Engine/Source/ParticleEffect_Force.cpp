#include "ParticleEffect_Force.h"

ParticleEffect_Force::ParticleEffect_Force() : ParticleEffect(ParticleEffectType::ACCELERATION_OVER_LIFETIME)
{
	type = ParticleEffectType::ACCELERATION_OVER_LIFETIME;
	gravity = -9.81f;
	force = 0.0f;
	direction = float3(0.0f, 0.0f, 0.0f);
}

ParticleEffect_Force::~ParticleEffect_Force()
{
}

void ParticleEffect_Force::Update(Particle& particle, float dt)
{
	if (hasGravity)
	{
		particle.acceleration.y += gravity;
	}

	particle.acceleration = direction.Normalized() * force;
}

void ParticleEffect_Force::OnEditor(int emitterIndex)
{
	float dir[3] = { direction[0], direction[1], direction[2] };

	std::string suffixLabel = "Force Over Lifetime Effect##";
	suffixLabel += emitterIndex;
	if (ImGui::CollapsingHeader(suffixLabel.c_str(), ImGuiTreeNodeFlags_Bullet))
	{
		suffixLabel = "Delete Force Over Lifetime Effect##";
		suffixLabel += emitterIndex;

		if (ImGui::Button(suffixLabel.c_str()))
			this->toDelete = true;

		ImGui::Spacing();
		ImGui::Indent();

		suffixLabel = "Force Type##ForceComboTitle";
		suffixLabel += emitterIndex;

		suffixLabel = "Force Direction##DirectionalForce";
		suffixLabel += emitterIndex;
		ImGui::DragFloat3(suffixLabel.c_str(), dir, 0.1f);

		direction[0] = dir[0];
		direction[1] = dir[1];
		direction[2] = dir[2];

		suffixLabel = "Force ##Force";
		suffixLabel += emitterIndex;
		ImGui::DragFloat(suffixLabel.c_str(), &force);

		ImGui::Unindent();
	}
}
