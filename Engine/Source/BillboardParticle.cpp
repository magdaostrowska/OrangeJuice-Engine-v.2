#include "BillboardParticle.h"
#include "ModuleScene.h"

BillboardParticle::BillboardParticle(GameObject* owner, ComponentType type, TransformComponent* trans)
{
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
	CameraComponent* cam = (CameraComponent*)app->scene->mainCamera->owner->GetComponent(ComponentType::CAMERA);
	float3 normal = (cam->transform->GetPosition() - this->transform->GetPosition().Normalized());
	float3 up = app->camera->cameraFrustum.Up();
	float3 right = normal.Cross(up);

	float3x3 mat = float3x3::identity;
	mat.Set(-right.x, -right.y, -right.z, up.x, up.y, up.z, normal.x, normal.y, normal.z);

	transform->rotation = mat.Inverted().ToQuat();

	/*float3 normal = (app->camera->Position - this->transform->position).Normalized();
	float3 up = App->camera->camera->frustum.up;
	float3 right = normal.Cross(up);

	float3x3 mat = float3x3::identity;
	mat.Set(-right.x, -right.y, -right.z, up.x, up.y, up.z, normal.x, normal.y, normal.z);

	transform->rotation = mat.Inverted().ToQuat();*/
}

//void BillboardParticle::Draw(Color color)
//{
//}

void BillboardParticle::OnEditor()
{
	if (ImGui::CollapsingHeader("Billboard"))
	{
		ImGui::PushItemWidth(90);
		ImGui::Separator();
	}
}
