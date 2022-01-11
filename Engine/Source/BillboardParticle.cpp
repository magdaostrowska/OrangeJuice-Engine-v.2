#include "BillboardParticle.h"
#include "ModuleScene.h"

BillboardParticle::BillboardParticle(GameObject* own, TransformComponent* trans)
{
	type = ComponentType::BILLBOARD;
	owner = own;
	transform = trans;
}

BillboardParticle::~BillboardParticle()
{
}

bool BillboardParticle::Update(float dt)
{
	return false;
}

void BillboardParticle::RotateToFaceCamera()
{
}

void BillboardParticle::OnEditor()
{
	if (ImGui::CollapsingHeader("Billboard"))
	{
		ImGui::PushItemWidth(90);
		ImGui::Separator();
	}
}
