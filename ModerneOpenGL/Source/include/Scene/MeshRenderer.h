#pragma once
#include "IComponent.h"
#include "Model.h"

class GameObject;
class MeshRenderer : public IComponent
{
public:
	MeshRenderer(GameObject* gameObject);
	MeshRenderer(GameObject* gameObject,std::string modelName);
	~MeshRenderer();

	void Update() override;
	void Delete() override;

	Model* model = nullptr;
	GameObject* gameObject;

	//recalculate MVP bool?
	Matrix4x4 MVP;
};


