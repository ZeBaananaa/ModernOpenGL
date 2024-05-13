#pragma once
#include "MathPerso.h"
#include "IComponent.h"
#include "Model.h"

class GameObject;

enum class Colliders
{
	SPHERE,
	CUBE,
	OTHER
};


class Collider : public IComponent
{
public:
	void AddCollider(Colliders colliderType, GameObject* _gameObject);
	Collider(Colliders colliderType, GameObject* _gameObject);
	~Collider();

	void Init() override;
	void Update() override;
	void Delete() override;

	Colliders type;

	Model* model = nullptr;
	GameObject* gameObject;
	Vector3D oldPos;
};

class SphereCollider : public Collider
{
public:
	SphereCollider(GameObject* _gameObject);
	~SphereCollider() = default;

	float radius = 0.5f;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* _gameObject);
	~BoxCollider();


};
