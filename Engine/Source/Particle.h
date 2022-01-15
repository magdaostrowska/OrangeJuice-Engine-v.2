#pragma once
#include "GameObject.h"
#include "ResourceManager.h"
#include "ModuleScene.h"
#include "glmath.h"
#include "MathGeoLib/src/Geometry/Frustum.h"

class Particle {

public:

	// This constructor is made to create the particle reference only
	Particle() {
		lifeTime = 10.0f;
		rotation = { 90.0f,0.0f,0.0f };
		acceleration = { 0.0f,0.0f,0.0f };
		size = { 0.5f,0.5f,0.5f };
		velocity = { 0.0f,0.0f,0.0f };
		position = { 0.0f,0.0f,0.0f };
		color = { 0, 0, 0 };
		tex = nullptr;
		isActive = true;

		//TODO: Particle Reference shoudn't have a plane
		plane = app->scene->CreateGameObject(app->scene->smoke1, true);
		plane->SetName("ParticleReference");
		plane->CreateComponent(ComponentType::MESH_RENDERER);
		plane->CreateComponent(ComponentType::BILLBOARD);

		ResourceManager::GetInstance()->LoadResource(std::string("Assets/Resources/plane.fbx"), *plane);
	}

	// This constructor should be used by default
	Particle(Particle* particleReference) 
	{
		lifeTime = particleReference->lifeTime;
		rotation = particleReference->rotation;
		acceleration = particleReference->acceleration;
		size = particleReference->size;
		velocity = particleReference->velocity;
		position = particleReference->position;
		color = particleReference->color;
		tex = particleReference->tex;
		isActive = particleReference->isActive;

		plane = app->scene->CreateGameObject(app->scene->smoke1, true);
		plane->SetName("Particle");
		plane->CreateComponent(ComponentType::MESH_RENDERER);
		plane->CreateComponent(ComponentType::BILLBOARD);

		ResourceManager::GetInstance()->LoadResource(std::string("Assets/Resources/plane.fbx"), *plane);
	}

public:

	float lifeTime;
	float3 rotation, acceleration;
	float3 size;
	float3 velocity, position, direction;
	Vec4 color;
	bool isActive;
	std::shared_ptr<Texture> tex;
	GameObject* plane;
};
