#pragma once
#include "Transform.h"
#include "SceneGraph.h"
#include "ResourcesManager.h"
#include <typeinfo>

class GameObject
{
public:
	GameObject(Transform* _parent = SceneGraph::Get().root);
	//modelName plus tard des enum genre cube sphere ect.
	GameObject(std::string modelName,Transform* _parent = SceneGraph::Get().root);

	~GameObject();

	void Update();

	std::string name = "";
	Transform* transform;
	std::vector<IComponent*> components;

	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;

		for (size_t i = 0; i < components.size(); i++)
		{
			if (typeid(components[i]).name() == T)
			{
				component = components[i];
				break;
			}
		}

		return component;
	}
};
