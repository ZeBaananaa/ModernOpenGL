#include "MeshRenderer.h"
#include "ResourcesManager.h"
#include "GameObject.h"
#include "Camera.h"

MeshRenderer::MeshRenderer(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

MeshRenderer::MeshRenderer(GameObject* gameObject,std::string modelName)
{
	this->gameObject = gameObject;
	this->model = ResourceManager::Get().Get<Model>(modelName);
}

void MeshRenderer::Update()
{
	if (model)
	{
		MVP = Camera::Get().GetVPMatrix() * gameObject->transform->GetGlobalTransform();
		// model->draw
	}
}

void MeshRenderer::Delete()
{
	delete this;
}
