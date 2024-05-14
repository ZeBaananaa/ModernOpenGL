#include "GameObject.h"
#include "Components.h"

int GameObject::index = 0;

GameObject::GameObject(Transform* _parent, std::string name)
{
	transform = new Transform(this, _parent);

	SetName(name);
}

GameObject::GameObject(std::string modelName, std::string textureName, std::string name, Transform* _parent, GLuint textureMode)
{
	transform = new Transform(this, _parent);

	SetName(name);

	!textureName.empty() ? components.push_back(new MeshRenderer(this, modelName, textureName, textureMode))
		: components.push_back(new MeshRenderer(this, modelName, "missing_texture.png", GL_REPEAT));

	++index;
}

GameObject::GameObject(Vector3D position, Vector3D rotation, Vector3D scale, std::string modelName, std::string textureName, std::string name, Transform* _parent, GLuint textureMode)
{
	transform = new Transform(position, rotation, scale, this, _parent);

	SetName(name);

		!textureName.empty() ? components.push_back(new MeshRenderer(this, modelName, textureName, textureMode))
		: components.push_back(new MeshRenderer(this, modelName, "missing_texture.png", GL_REPEAT));

	++index;
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Delete();

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

std::string GameObject::GetIndex() const
{
	return std::to_string(index);
}

void GameObject::AddComponent(IComponent* newComponent)
{
	if (newComponent)
		components.push_back(newComponent);
}

void GameObject::SetName(std::string name)
{
	if (name.empty())
		name = "GameObject " + GetIndex();

	transform->SetName(name);
}
