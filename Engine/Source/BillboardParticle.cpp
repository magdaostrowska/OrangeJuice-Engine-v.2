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

Quat BillboardParticle::RotateToFaceCamera()
{
	Frustum cameraFrustum = app->scene->mainCamera->camera;
	/*float3 billboard = (cameraFrustum.Pos() - transform->GetGlobalTransform().TranslatePart()).Normalized();

	float3 up = cameraFrustum.Up();
	float3 right = up.Cross(billboard);
	up = billboard.Cross(right);

	float3x3 mat = float3x3::identity;
	mat.Set(right.x, right.y, right.z, up.x, up.y, up.z, billboard.x, billboard.y, billboard.z);
	float3x3 matInverted = mat.Inverted();*/
	//app->scene->mainCamera->camera.rot
	Quat cameraRot = app->scene->mainCamera->currentRotation;
	float3 cameraRotationDegrees = cameraRot.ToEulerXYZ();
	
	//Quat ret = Quat::FromEulerXYZ();
	return cameraRot;
}

void BillboardParticle::OnEditor()
{
	if (ImGui::CollapsingHeader("Billboard"))
	{
		ImGui::PushItemWidth(90);
		ImGui::Separator();
	}
}
