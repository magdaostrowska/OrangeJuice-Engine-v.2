#pragma once
#include "Component.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

class BillboardParticle : public Component {

public:

	BillboardParticle(GameObject* own, TransformComponent* trans);
	~BillboardParticle();

	bool Update(float dt) override;
	void RotateToFaceCamera(); //Billboard particles are flat textured quads that are rotated to always face the camera

	void OnEditor() override;

public:

	TransformComponent* transform;
};