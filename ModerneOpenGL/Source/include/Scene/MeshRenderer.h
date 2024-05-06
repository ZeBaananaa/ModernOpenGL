#pragma once
#include "IComponent.h"
#include "Model.h"
#include <Resources/Texture.h>

class GameObject;
class MeshRenderer : public IComponent
{
public:
	MeshRenderer(GameObject* gameObject);
	MeshRenderer(GameObject* gameObject, std::string modelName, std::string textureName);
	~MeshRenderer();

	void Update() override;
	void Delete() override;

	Model* model = nullptr;
	Texture* texture = nullptr;
	GameObject* gameObject;

	//recalculate MVP bool?
	Matrix4x4 MVP;
};


