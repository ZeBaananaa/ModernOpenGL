#pragma once
#include "Model.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	Model* model{ nullptr };

	Matrix4x4 modelMatrix;
	Matrix4x4 mvpMatrix;
};
