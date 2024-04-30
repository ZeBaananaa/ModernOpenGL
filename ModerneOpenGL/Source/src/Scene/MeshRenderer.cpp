#include "MeshRenderer.h"
#include "ResourcesManager.h"

MeshRenderer::MeshRenderer(std::string modelName)
{
	this->model = ResourceManager::Get().Get<Model>(modelName);
}

void MeshRenderer::Update()
{
	//if(model)
	// model->draw	
}

void MeshRenderer::Delete()
{
	delete this;
}
