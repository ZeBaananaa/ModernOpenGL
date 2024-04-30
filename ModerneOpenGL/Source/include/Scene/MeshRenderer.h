#pragma once
#include "IComponent.h"
#include "Model.h"

class MeshRenderer : public IComponent
{
public:
	MeshRenderer() =  default;
	MeshRenderer(std::string modelName);
	~MeshRenderer() = default;

	void Update() override;
	void Delete() override;

	Model* model = nullptr;

};


