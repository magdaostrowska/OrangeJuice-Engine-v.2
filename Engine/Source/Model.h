#pragma once

#include "Resource.h"
#include <vector>
#include "GameObject.h"

typedef unsigned int uint;

struct ModelParameters
{
	bool flippedUvs = true;
	bool optimizedMesh = true;
	bool normals = true;
	bool genSmoothNormals = false;
	bool splitLargeMeshes = true;
	bool removeRedundantMaterials = false;
	bool genUVCoords = false;
	bool optimizeGraph = false;
	bool debone = false;
};

class Model : public Resource
{
public:
	Model(uint uid, std::string& assets, std::string& library);

	~Model();

	void Load() override;
	void LoadParticle(GameObject& particle);

	void DrawOnEditor() override;

	inline void SetMeshes(std::vector<uint>& meshesUids) { meshes = meshesUids; }

private:
	void Reimport();

	ModelParameters parameters;

	std::vector<uint> meshes;
};