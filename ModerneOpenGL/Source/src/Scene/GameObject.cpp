#include "GameObject.h"
#include "Components.h"

GameObject::GameObject(Transform* _parent)
{
	transform = new Transform(this,_parent);
}

GameObject::GameObject(std::string modelName, std::string textureName, GLuint textureMode, Transform* _parent)
{
	transform = new Transform(this, _parent);
	textureName != "" ? components.push_back(new MeshRenderer(this, modelName, textureName, textureMode))
		: components.push_back(new MeshRenderer(this, modelName, "missing_texture.png", GL_REPEAT));
}

GameObject::GameObject(Vector3D position, Vector3D rotation, Vector3D scale, std::string modelName, std::string textureName, GLuint textureMode, Transform* _parent)
{
	transform = new Transform(position,rotation,scale,this, _parent);
	textureName != "" ? components.push_back(new MeshRenderer(this, modelName, textureName, textureMode))
		: components.push_back(new MeshRenderer(this, modelName, "missing_texture.png", GL_REPEAT));
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Delete();
	}
	components.clear();
	transform = nullptr;
}

void GameObject::Update()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		MeshRenderer* component = dynamic_cast<MeshRenderer*>(components[i]);
		if (component == nullptr)
			components[i]->Update();
	}
}

void GameObject::AddComponent(IComponent* newComponent)
{
	if (newComponent)
	{
		components.push_back(newComponent);
	}
}
