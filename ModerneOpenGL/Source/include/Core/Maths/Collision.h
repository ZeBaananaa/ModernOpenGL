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
	virtual void Update() = 0;
	void Delete() override;

	virtual void Resize() = 0;
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
	void Resize() override;

	float scale = 0.f;
	float radius = 0.5f;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* _gameObject);
	~BoxCollider() = default;

	void Update() override;
	void Resize() override;
	Vector3D scale = { 1,1,1 };
	Vector3D size = { 1,1,1 };
};

Collider* AddCollider(Colliders colliderType, GameObject* _gameObject);

bool CollisionSphereSphere(SphereCollider* s1, SphereCollider* s2);

bool QuickCheck(SphereCollider* s, BoxCollider* b);
bool CollisionSphereBox(SphereCollider* s, BoxCollider* b);

bool CollisionSegmentQuads(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Matrix4x4 globalMatrixOfBox);
bool CollisionSegmentQuad(Vector3D startSeg, Vector3D endSeg, Vector3D normal, float lenght,float height, Vector3D& posCol, Matrix4x4 worldTransform);
bool CollisionSegmentPlan(Vector3D startSeg, Vector3D endSeg, Vector3D normal, Vector3D& posCol, Matrix4x4 worldTransform);

bool CollisionSegmentSpheres(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Matrix4x4 globalMatrixOfBox);
bool CollisionSegmentSphere(Vector3D startSeg, Vector3D endSeg, Vector3D posSphere, float radius, Vector3D& posCol,Matrix4x4 worldTransform);

bool CollisionCyliders(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Matrix4x4 globalMatrixOfBox);
bool CollisionSegmentCylinder(Vector3D startSeg, Vector3D endSeg, Vector3D startEdge, Vector3D endEdge, float radius, Vector3D& posCol, Matrix4x4 worldTransform);