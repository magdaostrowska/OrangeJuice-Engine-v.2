#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(ParticleEffectType type)
{
	this->type = type;
	toDelete = false;
}

ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::Init(Particle& particle)
{
}

void ParticleEffect::Update(Particle& particle, float dt)
{
}

void ParticleEffect::OnEditor(int emitterIndex)
{
}

bool ParticleEffect::OnLoad(JsonParsing& node)
{
	toDelete = node.GetJsonBool("PE: To Delete");
	return true;
}

bool ParticleEffect::OnSave(JsonParsing& node, JSON_Array* array)
{
	JsonParsing file = JsonParsing();
	file.SetNewJsonBool(file.ValueToObject(file.GetRootValue()), "PE: To Delete", toDelete);
	//file.SetNewJsonString(file.ValueToObject(file.GetRootValue()), "Type", type.c_str);
	node.SetValueToArray(array, file.GetRootValue());
	return true;
}
