#include "ParticleEffect_Size.h"

ParticleEffect_Size::ParticleEffect_Size() : ParticleEffect(ParticleEffectType::SIZE_OVER_LIFETIME)
{
	type = ParticleEffectType::SIZE_OVER_LIFETIME;
	startSize = { 0.1f, 0.1f};
	endSize = { 1.0f, 1.0f };
}

ParticleEffect_Size::~ParticleEffect_Size()
{
}

void ParticleEffect_Size::Update(Particle& particle, float dt)
{
	if (particle.isActive)
	{
		float percentatge = particle.lifeTime / 10;
		particle.size.x = (1 - percentatge) * endSize[0] + percentatge * startSize[0];
		particle.size.z = (1 - percentatge) * endSize[1] + percentatge * startSize[1];
	}
}

void ParticleEffect_Size::OnEditor(int emitterIndex)
{
	float start[2] = { startSize[0],startSize[1] };
	float end[2] = { endSize[0],endSize[1] };
	float minSize = 0.0f;
	float maxSize = 1.0f;

	std::string suffixLabel = "Size Over Lifetime Effect##";
	suffixLabel += emitterIndex;

	if (ImGui::CollapsingHeader(suffixLabel.c_str(), ImGuiTreeNodeFlags_Bullet))
	{
		suffixLabel = "Delete Effect##";
		suffixLabel += emitterIndex;

		if (ImGui::Button(suffixLabel.c_str()))
			this->toDelete = true;

		ImGui::Spacing();
		ImGui::Indent();

		suffixLabel = "Initial Size##SizeOverLife";
		suffixLabel += emitterIndex;
		ImGui::DragFloat2(suffixLabel.c_str(), start, 0.1f, minSize, maxSize);
		startSize = { start[0] , start[1]};

		suffixLabel = "End Size##SizeOverLife";
		suffixLabel += emitterIndex;
		ImGui::DragFloat2(suffixLabel.c_str(), end, 0.1f, minSize, maxSize);
		endSize = { end[0] , end[1] };

		ImGui::Unindent();
	}
}

bool ParticleEffect_Size::OnLoad(JsonParsing& node)
{
	toDelete = node.GetJsonBool("PES: To Delete");
	return true;
}

bool ParticleEffect_Size::OnSave(JsonParsing& node, JSON_Array* array)
{
	JsonParsing file = JsonParsing();
	file.SetNewJsonBool(file.ValueToObject(file.GetRootValue()), "PES: To Delete", toDelete);
	//*************************************///
	node.SetValueToArray(array, file.GetRootValue());
	return true;
}
