#include "GameObject.h"
#include "Components.h"

GameObject::GameObject(Transform* _parent)
{
	transform = new Transform(this,_parent);
}

GameObject::GameObject(std::string modelName, Transform* _parent)
{
	transform = new Transform(this, _parent);
	components.push_back(new MeshRenderer(modelName));
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Delete();
	}
	components.clear();
}

void GameObject::Update()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if(typeid(components[i]).name() != "MeshRenderer")
			components[i]->Update();
	}
}