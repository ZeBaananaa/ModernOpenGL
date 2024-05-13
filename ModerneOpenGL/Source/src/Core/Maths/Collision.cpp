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
		_gameObject->AddComponent(new BoxCollider(_gameObject));
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
	gameObject = nullptr;
}

void Collider::Init()
{
}

void Collider::Update()
{
}

void Collider::Delete()
{
	delete this;
}

SphereCollider::SphereCollider(GameObject* _gameObject)
	:Collider(Colliders::SPHERE,_gameObject)
{
	radius = 0.5f;
}

void SphereCollider::Update()
{
	Vector3D scaleL = gameObject->transform->GetLocalScale();

	scale = scaleL.x;
	for (int i = 1; i < 3; ++i)
	{
		if (scale < scaleL[i])
			scale = scaleL[i];
	}

	SceneGraph::Get().root->CheckCollision(this);
	oldPos = gameObject->transform->GetGlobalPosition();
}

BoxCollider::BoxCollider(GameObject* _gameObject)
	:Collider(Colliders::CUBE, _gameObject)
{
}

void BoxCollider::Update()
{
	scale = gameObject->transform->GetLocalScale();

	//SceneGraph::Get().root->CheckCollision(this);
	//oldPos = gameObject->transform->GetGlobalPosition();
}

bool CollisionSphereSphere(SphereCollider* s1, SphereCollider* s2)
{
	if (Distance(s1->gameObject->transform->GetGlobalPosition(), s2->gameObject->transform->GetGlobalPosition())
		< s1->radius * s1->scale + s1->radius * s1->scale)
		return true;
	
	return false;
}

bool CollisionSphereBox(SphereCollider* collider, BoxCollider* box)
{
	//peu etre collision s/s avant pour check

	float radiusScaled = collider->radius * collider->scale;

	Matrix4x4 rg = Reverse(box->gameObject->transform->GetGlobalTransform());
	Vector3D positionOldSphereL = rg * Vector4D(collider->oldPos);
	Vector3D positionSphereL = rg * Vector4D(collider->gameObject->transform->GetGlobalPosition());

	Vector3D sizeScaled = TensorialProduct(box->size, box->scale);

	std::vector<Vector3D> points;
	points.push_back({ -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f });
	points.push_back({ -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f });

	points.push_back({ -sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f });
	points.push_back({ -sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f });

	//Vector3D p0 = { -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f };
	//Vector3D p1 = { -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f };
	//Vector3D p2 = { sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f };
	//Vector3D p3 = { sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f };

	//Vector3D p4 = { -sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f };
	//Vector3D p5 = { -sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f };
	//Vector3D p6 = { sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f };
	//Vector3D p7 = { sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f };


	for (int i = 0; i < 4; ++i)
	{
		int j = i + 1;
		if (i == 3)
			j = 0;

		//caps horizontal
			//bottom
		if (CollisionSegmentCylinder(positionOldSphereL, positionSphereL, points[i], points[j], radiusScaled))
			return true;
		if (CollisionSegmentSphere(positionOldSphereL, positionSphereL, points[i], radiusScaled))
			return true;
		//top
		if (CollisionSegmentCylinder(positionOldSphereL, positionSphereL, points[i + 4], points[j + 4], radiusScaled))
			return true;
		if (CollisionSegmentSphere(positionOldSphereL, positionSphereL, points[i+4], radiusScaled))
			return true;

		//caps vertical
		if (CollisionSegmentCylinder(positionOldSphereL, positionSphereL, points[i], points[i + 4], radiusScaled))
			return true;
	}

	for (int i = 0; i < 6; ++i)
	{
		//faces 0.x + radius 0.y+radius 0.z + radius par exemple
		// face carre mais plus petite de tte les composantes de +/- radius
		//Seg Quad ->> Plan true? -> quad ?
	}

	return false;
}
