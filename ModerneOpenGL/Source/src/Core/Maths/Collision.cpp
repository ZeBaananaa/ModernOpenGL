#include "Collision.h"
#include "GameObject.h"
#include "SceneGraph.h"
#include "Log.h"
#include "ResourcesManager.h"

void Collider::AddCollider(Colliders colliderType, GameObject* _gameObject)
{
	switch (colliderType)
	{
	case Colliders::SPHERE:
		_gameObject->AddComponent(new SphereCollider(_gameObject));
		break;
	case Colliders::CUBE:
		break;
	case Colliders::OTHER:
		break;
	}
}

Collider::Collider(Colliders colliderType, GameObject* _gameObject)
{
	type = colliderType;
	gameObject = _gameObject;
	if (gameObject == nullptr)
		DEBUG_LOG("gameobject nullptr");
}

Collider::~Collider()
{
	model = nullptr;
	gameObject = nullptr;
}

void Collider::Init()
{
}

void Collider::Update()
{
	SceneGraph::Get().root->CheckCollision(this);
	oldPos = gameObject->transform->GetGlobalPosition();
}

void Collider::Delete()
{
	delete this;
}

SphereCollider::SphereCollider(GameObject* _gameObject)
	:Collider(Colliders::SPHERE,_gameObject)
{
	radius = 0.5f;
	model = ResourceManager::Get().Get<Model>("sphere.obj");
}