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
		lifeTime = 1.5f;
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

	bool OnLoad(JsonParsing& node) 
	{
		lifeTime = node.GetJsonNumber("Particle: LifeTime");
		rotation = node.GetJson3Number(node, "Particle: Rotation");
		acceleration = node.GetJson3Number(node, "Particle: Acceleration");
		size = node.GetJson3Number(node, "Particle: Size");
		velocity = node.GetJson3Number(node, "Particle: Velocity");
		position = node.GetJson3Number(node, "Particle: Position");
		direction = node.GetJson3Number(node, "Particle: Direction");;
		isActive = node.GetJsonBool("Particle: Is Active");
		return true;
	}

	bool OnSave(JsonParsing& node, JSON_Array* array) 
	{
		JsonParsing file = JsonParsing();
		file.SetNewJsonNumber(file.ValueToObject(file.GetRootValue()), "Particle: LifeTime", lifeTime);
		file.SetNewJson3Number(file, "Particle: Rotation", rotation);
		file.SetNewJson3Number(file, "Particle: Acceleration", acceleration);
		file.SetNewJson3Number(file, "Particle: Size", size);
		file.SetNewJson3Number(file, "Particle: Velocity", velocity);
		file.SetNewJson3Number(file, "Particle: Position", position);
		file.SetNewJson3Number(file, "Particle: Direction", direction);
		//file.SetNewJson4Number(file, "Particle: Direction", Quat::FromEulerXYX(color));
		//
		file.SetNewJsonBool(file.ValueToObject(file.GetRootValue()), "Particle: Is Active", isActive);
		node.SetValueToArray(array, file.GetRootValue());
		return true;
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
