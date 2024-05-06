#pragma once
#include "IComponent.h"
#include "Components.h"
#include "SceneGraph.h"
#include "ResourcesManager.h"
#include <typeinfo>

class GameObject
{
public:
	GameObject(Transform* _parent = SceneGraph::Get().root);
	//modelName plus tard des enum genre cube sphere ect.
	GameObject(std::string modelName,Transform* _parent = SceneGraph::Get().root);

	GameObject(Vector3D position, Vector3D rotation, Vector3D scale
		,std::string modelName, Transform* _parent = SceneGraph::Get().root);



	~GameObject();

	void Update();

	Transform* transform = nullptr;
	std::vector<IComponent*> components;

	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component != nullptr)
				return component;
		}

		return nullptr;
	}
	void AddComponent(IComponent* newComponent);
};
