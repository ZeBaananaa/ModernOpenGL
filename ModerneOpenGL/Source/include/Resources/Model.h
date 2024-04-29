#pragma once
#include <string>
#include <vector>
#include "Vertex.h"
#include "ResourcesManager.h"

class Model : public IResource
{
public:
	Model(std::string nameObjFile);
	~Model();

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indeces;

	void UnLoad()override;
private:
	void Load(std::string nameObjFile) override;
};