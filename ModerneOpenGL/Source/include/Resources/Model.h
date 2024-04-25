#pragma once
#include <string>
#include <vector>
#include "Vertex.h"

class Model
{
public:
	Model(std::string nameObjFile);
	~Model();

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indeces;

private:
	void LoadModel(std::string nameObjFile);


};