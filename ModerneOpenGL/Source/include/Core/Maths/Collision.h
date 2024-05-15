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
	void Init() override;
	virtual void Update();
	void Delete() override;

	Colliders type;

	GameObject* gameObject;
	Vector3D oldPos;

protected:
	Collider(Colliders colliderType, GameObject* _gameObject);
	~Collider();
};

class SphereCollider : public Collider
{
public:
	SphereCollider(GameObject* _gameObject);
	~SphereCollider() = default;

	void Update() override;
	float scale = 0.f;
	float radius = 0.5f;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* _gameObject);
	~BoxCollider() = default;

	void Update() override;
	Vector3D scale = { 1,1,1 };
	Vector3D size = { 1,1,1 };
};

Collider* AddCollider(Colliders colliderType, GameObject* _gameObject);

bool CollisionSphereSphere(SphereCollider* s1, SphereCollider* s2);

//put s pos et old pos in local and at the end put the pos(t0) in global pos
bool CollisionSphereBox(SphereCollider* s, BoxCollider* b);

bool CollisionSegmentPlan();
bool CollisionSegmentQuad();

bool CollisionSegmentCapsule(Vector3D startSeg, Vector3D endSeg, Vector3D startEdge, Vector3D endEdge, float radius);
bool CollisionSegmentSphere(Vector3D startSeg, Vector3D endSeg, Vector3D posSphere, float radius, Vector3D& posCol,Matrix4x4 worldTransform);
bool CollisionSegmentCylinder(Vector3D startSeg, Vector3D endSeg, Vector3D startEdge, Vector3D endEdge, float radius, Vector3D& posCol);