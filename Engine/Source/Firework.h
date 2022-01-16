#pragma once
#include "Emitter.h"
#include "GameObject.h"
#include "MathGeoLib/src/Algorithm/Random/LCG.h"

class Firework : Emitter {

public:
	Firework(GameObject* owner);
	void Update(float dt) override;
	void Emit(float dt) override;

	bool OnLoad(JsonParsing& node) override;
	bool OnSave(JsonParsing& node, JSON_Array* array) override;

public:

	float limitY;
	bool directionChanged;
};