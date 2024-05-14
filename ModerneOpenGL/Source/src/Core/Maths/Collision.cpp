#include "Collision.h"
#include "GameObject.h"
#include "SceneGraph.h"
#include "Log.h"
#include "ResourcesManager.h"

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


SphereCollider::SphereCollider(GameObject* _gameObject)
	:Collider(Colliders::SPHERE, _gameObject)
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

Collider* AddCollider(Colliders colliderType, GameObject* _gameObject)
{
	switch (colliderType)
	{
	case Colliders::SPHERE:
		return new SphereCollider(_gameObject);
		break;
	case Colliders::CUBE:
		return new BoxCollider(_gameObject);
		break;
	case Colliders::OTHER:
		break;
	}
}

bool CollisionSphereSphere(SphereCollider* s1, SphereCollider* s2)
{
	if (Distance(s1->gameObject->transform->GetGlobalPosition(), s2->gameObject->transform->GetGlobalPosition())
		<= s1->radius * s1->scale*2.f + s2->radius * s2->scale*2.f)
		return true;

	return false;
}

bool CollisionSphereBox(SphereCollider* collider, BoxCollider* box)
{
	//peu etre collision s/s avant pour check

	float radiusScaled = collider->radius * collider->scale*2.f;

	Matrix4x4 g = box->gameObject->transform->GetGlobalTransform();
	Matrix4x4 rg = Reverse(g);
	Vector3D positionOldSphereL = rg * Vector4D(collider->oldPos);
	Vector3D positionSphereL = rg * Vector4D(collider->gameObject->transform->GetGlobalPosition());

	if (positionOldSphereL == positionSphereL)
		return false;

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

	Vector3D posCol = {10000,10000,10000};
	bool col = false;

	for (int i = 0; i < 2; ++i)
	{
		Vector3D rota{90,0,0};
		if (i == 1)
			rota = {0,0,90};

		int j = i + 1;

		Matrix4x4 trsCylinder = TRS(MidPoint(points[i], points[j]),rota,Vector3D::one);
		Matrix4x4 trsCylinderR = Reverse(trsCylinder);
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL, trsCylinderR * (Vector4D)points[i], trsCylinderR * (Vector4D)points[j], radiusScaled, posCol))
		{
			posCol = trsCylinder * (Vector4D)posCol;
			col = true;
		}

		int k = 1;
		if (i == 1)
			k = 0;

		trsCylinder = TRS(MidPoint(points[i+2], points[(j + 2) * k]), rota, Vector3D::one);
		trsCylinderR = Reverse(trsCylinder);
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL, trsCylinderR * (Vector4D)points[i+2], trsCylinderR * (Vector4D)points[(j+2)*k], radiusScaled, posCol))
		{
			posCol = trsCylinder * (Vector4D)posCol;
			col = true;
		}

		trsCylinder = TRS(MidPoint(points[i+4], points[j+4]), rota, Vector3D::one);
		trsCylinderR = Reverse(trsCylinder);
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL, trsCylinderR * (Vector4D)points[i + 4], trsCylinderR * (Vector4D)points[j + 4], radiusScaled, posCol))
		{
			posCol = trsCylinder * (Vector4D)posCol;
			col = true;
		}

		int k2 = j + 6;
		if (i == 1)
			k2 = 4;

		trsCylinder = TRS(MidPoint(points[i + 6], points[k2]), rota, Vector3D::one);
		trsCylinderR = Reverse(trsCylinder);
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * Vector4D(points[i + 6]), trsCylinderR * Vector4D(points[k2]), radiusScaled, posCol))
		{
			posCol = trsCylinder * (Vector4D)posCol;
			col = true;
		}
	}
	if (col)
	{
		posCol = box->gameObject->transform->GetGlobalTransform() * (Vector4D)posCol;

		Vector3D realPos = posCol - collider->gameObject->transform->GetGlobalPosition();
		collider->gameObject->transform->SetLocalPosition(collider->gameObject->transform->GetLocalPosition() + realPos);

		return true;
	}

	for (int i = 0; i < 4; ++i)
	{
		//caps horizontal
			//bottom

		if (CollisionSegmentSphere(positionOldSphereL, positionSphereL, points[i], radiusScaled, posCol))
		{
			col = true;
		}
		//top

		if (CollisionSegmentSphere(positionOldSphereL, positionSphereL, points[i + 4], radiusScaled, posCol))
		{
			col = true;
		}

		//caps vertical
		if (CollisionSegmentCylinder(positionOldSphereL, positionSphereL, points[i], points[i + 4], radiusScaled, posCol))
		{
			col = true;
		}
	}
	if (col)
	{
		posCol = box->gameObject->transform->GetGlobalTransform() * (Vector4D)posCol;

		Vector3D realPos = posCol - collider->gameObject->transform->GetGlobalPosition();
		collider->gameObject->transform->SetLocalPosition(collider->gameObject->transform->GetLocalPosition() + realPos);

		return true;
	}
	else
	{
		//for (int i = 0; i < 6; ++i)
		//{
		//	//faces 0.x + radius 0.y+radius 0.z + radius par exemple
		//	// face carre mais plus petite de tte les composantes de +/- radius
		//	//Seg Quad ->> Plan true? -> quad ?
		//}

	}

	if (col)
	{
		//
		return true;
	}
	return false;
}

bool CollisionSegmentSphere(Vector3D startSeg, Vector3D endSeg, Vector3D posSphere, float radius, Vector3D& posCol)
{
	Vector3D AB(startSeg, endSeg);
	float a = AB.SquaredNorm();
	Vector3D CA(posSphere, startSeg);
	float b = DotProduct(AB * 2.f, CA);
	float c = CA.SquaredNorm() - (radius * radius);

	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return false;

	float t0 = (-b - sqrtf(delta)) / (2 * a);

	if (t0 > 1 || t0 < 0)
		return false;

	if (Norm(startSeg + posCol) > Norm(startSeg + AB * t0))
		posCol = startSeg + AB * t0;

	return true;
}

bool CollisionSegmentCylinder(Vector3D startSeg, Vector3D endSeg, Vector3D startEdge, Vector3D endEdge, float radius, Vector3D& posCol)
{
	Vector3D AB(startSeg, endSeg);

	float a = AB.x * AB.x + AB.y * AB.y;
	float b = 2 * (AB.x * startSeg.x + AB.y * startSeg.y);
	float c = (startSeg.x * startSeg.x) + (startSeg.y * startSeg.y) - (radius * radius);

	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return false;

	float t0 = (-b - sqrtf(delta)) / (2 * a);

	Vector3D posCollision = startSeg + AB * t0;


	if ((startEdge.y > posCollision.y && posCollision.y > endEdge.y) || (endEdge.y > posCollision.y && posCollision.y > startEdge.y))
	{
		if (Norm(startSeg + posCol) > Norm(posCollision))
			posCol = posCollision;

		return true;
	}
	
	return false;
}