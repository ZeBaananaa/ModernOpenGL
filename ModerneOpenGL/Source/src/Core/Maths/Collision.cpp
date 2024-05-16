#include "Collision.h"
#include "GameObject.h"
#include "SceneGraph.h"
#include "Log.h"
#include "ResourcesManager.h"

void Collider::Init()
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
	Resize();

	//SceneGraph::Get().root->CheckCollision(this);
	oldPos = gameObject->transform->GetGlobalPosition();
}

void SphereCollider::Resize()
{
	Vector3D scaleL = gameObject->transform->GetLocalScale();

	scale = scaleL.x;
	for (int i = 1; i < 3; ++i)
	{
		if (scale < scaleL[i])
			scale = scaleL[i];
	}
	scale *= 2.f;
}

BoxCollider::BoxCollider(GameObject* _gameObject)
	:Collider(Colliders::CUBE, _gameObject)
{
}

void BoxCollider::Update()
{
	Resize();

	//SceneGraph::Get().root->CheckCollision(this);
	//oldPos = gameObject->transform->GetGlobalPosition();
}

void BoxCollider::Resize()
{
	scale = gameObject->transform->GetLocalScale();
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
		<= s1->radius * s1->scale + s2->radius * s2->scale)
		return true;

	return false;
}

bool QuickCheck(SphereCollider* s, BoxCollider* b)
{
	//use only for do it fast because if the sphere go trought is doesn't detect the col
	s->Resize();
	SphereCollider* s2 = new SphereCollider(b->gameObject);
	s2->Resize();

	Transform* t = b->gameObject->transform;
	GameObject* sol = new GameObject(t->GetGlobalPosition(), t->GetGlobalRotation(), s2->radius * s2->scale, "sphere.obj", "missing_texture.jpg");

	if (!CollisionSphereSphere(s, s2))
	{
		s2->Delete();
		return false;
	}
	s2->Delete();
	return true;
}

bool CollisionSphereBox(SphereCollider* collider, BoxCollider* box)
{
	float radiusScaled = collider->radius * collider->scale;
	Vector3D sizeScaled = TensorialProduct(box->size, box->scale);

	Matrix4x4 g = box->gameObject->transform->GetGlobalTransform();
	Matrix4x4 rg = Reverse(g);

	//Vector3D inverseScale = box->gameObject->transform->GetGlobalScale();
	//inverseScale.x = 1.0f / inverseScale.x;
	//inverseScale.y = 1.0f / inverseScale.y;
	//inverseScale.z = 1.0f / inverseScale.z;

	//Vector3D value = box->gameObject->transform->GetGlobalRotation() * -1;
	//Matrix4x4 trss = TRS(box->gameObject->transform->GetGlobalPosition() * -1, value, inverseScale);
	
	Vector3D positionOldSphereL = rg * Vector4D(collider->oldPos);
	Vector3D positionSphereL = rg * Vector4D(collider->gameObject->transform->GetGlobalPosition());

	if (positionOldSphereL == positionSphereL)
		return false;

	std::vector<Vector3D> points;
	points.push_back({ -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f } );
	points.push_back({ -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f });

	points.push_back({ -sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f });
	points.push_back({ -sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f });


	/// DEBUG ///
	for (size_t i = 0; i < points.size(); i++)
	{
		GameObject* g = new GameObject(points[i],Vector3D::zero,Vector3D::one * 0.2f,"cube.obj");
	}

	GameObject* c = new GameObject(positionOldSphereL, box->gameObject->transform->GetGlobalRotation(), Vector3D::one * 0.5f, "cube.obj");
	GameObject* d = new GameObject(positionSphereL, box->gameObject->transform->GetGlobalRotation(), Vector3D::one * 0.3f, "cube.obj");
	//////////

	Vector3D posCol = {10000,10000,10000};

	 bool col = CollisionSegmentSpheres(points, positionOldSphereL, positionSphereL, radiusScaled, posCol, g);
	 col = CollisionCyliders(points, positionOldSphereL, positionSphereL, radiusScaled, posCol, g);

	if (col)
	{
		GameObject* g = new GameObject(posCol, Vector3D::zero, Vector3D::one * 0.2f, "sphere.obj");

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


bool CollisionSegmentQuads(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Matrix4x4 globalMatrixOfBox)
{
	bool col = false;

	for (int i = 0; i < 2; ++i)
	{
		Matrix4x4 trsCylinder = TRS(MidPoint(points[i] - radiusScaled, points[i + 2] - radiusScaled), {90,0,0}, Vector3D::one);
		Matrix4x4 trsCylinderR = Reverse(trsCylinder);
		posCol = trsCylinderR * (Vector4D)posCol;

		Vector3D pointsI = trsCylinderR * (Vector4D)points[i] - radiusScaled;
		float lenghtSide0 = Distance(pointsI, (Vector3D)(trsCylinderR * (Vector4D)points[i + 1] - radiusScaled));
		float lenghtSide1 = Distance(pointsI, (Vector3D)(trsCylinderR * (Vector4D)points[i + 3] - radiusScaled));

		float L = lenghtSide0 / 2.f;
		float H = lenghtSide1 / 2.f;

		if (CollisionSegmentQuad(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, Vector3D::axeY ,L ,H, posCol, globalMatrixOfBox * trsCylinder))
		{
			col = true;

		}
		posCol = trsCylinder * (Vector4D)posCol;
		GameObject* sol = new GameObject(posCol, Vector3D::zero, Vector3D::one * 0.1f, "cube.obj", "black.png");
	}

	return col;
}

bool CollisionSegmentQuad(Vector3D startSeg, Vector3D endSeg, Vector3D normal,float lenght, float height, Vector3D& posCol, Matrix4x4 worldTransform)
{
	Vector3D posColPlan;
	if (!CollisionSegmentPlan(startSeg, endSeg, normal, posColPlan, worldTransform))
		return false;

	if(fabsf(posColPlan.x) <= lenght && fabsf(posColPlan.y) <= height)
	{
		Vector3D worldPosCol = worldTransform * Vector4D(posCol);
		Vector3D worldstartSeg = worldTransform * Vector4D(startSeg);
		Vector3D worldNewPosCol = worldTransform * Vector4D(posColPlan);
		if (Norm(worldPosCol - worldstartSeg) > Norm(worldNewPosCol - worldstartSeg))
			posCol = posColPlan;
		return true;
	}
	return false;
}

bool CollisionSegmentPlan(Vector3D startSeg, Vector3D endSeg, Vector3D normal, Vector3D& posCol, Matrix4x4 worldTransform)
{
	Vector3D AB(startSeg, endSeg);
	float dot = DotProduct(AB, normal);
	if (dot == 0)
		return false;

	//if local of a face, it hit the center 0,0,0 of the face
	Vector3D center = Vector3D::zero;
	float d = -(normal.x * center.x + normal.y * center.y + normal.z * center.z);
	float t0 = -(DotProduct(startSeg, normal) + d) / dot;

	if (t0 > 1 || t0 < 0)
		return false;

	posCol = startSeg + AB * t0;

	return true;	
}

bool CollisionSegmentSpheres(std::vector<Vector3D> points,Vector3D positionOldSphereL,Vector3D positionSphereL,float radiusScaled,Vector3D& posCol,Matrix4x4 globalMatrixOfBox)
{
	bool col = false;
	for (int i = 0; i < 4; ++i)
	{
		//bottom
		if (CollisionSegmentSphere(positionOldSphereL, positionSphereL, points[i], radiusScaled, posCol, globalMatrixOfBox))
		{
			col = true;
			GameObject* sol = new GameObject(posCol, { 45,45,45 }, Vector3D::one * 0.1f, "cube.obj", "black.png");
		}

		//top
		if (CollisionSegmentSphere(positionOldSphereL, positionSphereL, points[i + 4], radiusScaled, posCol, globalMatrixOfBox))
		{
			col = true;
			GameObject* sol = new GameObject(posCol, { 45,45,45 }, Vector3D::one * 0.1f, "cube.obj", "black.png");
		}
	}

	return col;
}

bool CollisionSegmentSphere(Vector3D startSeg, Vector3D endSeg, Vector3D posSphere, float radius, Vector3D& posCol,Matrix4x4 worldTransform)
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


	Vector3D worldPosCol = worldTransform * Vector4D(posCol);
	Vector3D worldstartSeg = worldTransform * Vector4D(startSeg);
	Vector3D worldNewPosCol = worldTransform * Vector4D(startSeg + AB * t0);

	if (Norm(worldPosCol - worldstartSeg) > Norm(worldNewPosCol - worldstartSeg))
		posCol = startSeg + AB * t0;


	return true;
}

bool CollisionCyliders(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Matrix4x4 globalMatrixOfBox)
{
	bool col = false;

	//cylinder horizontal
	for (int i = 0; i < 2; ++i)
	{
		Vector3D rota{ 90,0,0 };
		if (i == 1)
			rota = { 0,0,90 };

		int j = i + 1;

		Matrix4x4 trsCylinder = TRS(MidPoint(points[i], points[j]), rota, Vector3D::one);
		Matrix4x4 trsCylinderR = Reverse(trsCylinder);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * (Vector4D)points[i], trsCylinderR * (Vector4D)points[j], radiusScaled, posCol, globalMatrixOfBox * trsCylinder))
		{
			col = true;

		}
		posCol = trsCylinder * (Vector4D)posCol;
		GameObject* sol = new GameObject(posCol, Vector3D::zero, Vector3D::one * 0.1f, "cube.obj", "black.png");

		int k = 1;
		if (i == 1)
			k = 0;

		trsCylinder = TRS(MidPoint(points[i + 2], points[(j + 2) * k]), rota, Vector3D::one);
		trsCylinderR = Reverse(trsCylinder);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * (Vector4D)points[i + 2], trsCylinderR * (Vector4D)points[(j + 2) * k], radiusScaled, posCol, globalMatrixOfBox * trsCylinder))
		{
			col = true;

		}
		posCol = trsCylinder * (Vector4D)posCol;
		sol = new GameObject(posCol, Vector3D::zero, Vector3D::one * 0.1f, "cube.obj", "black.png");

		trsCylinder = TRS(MidPoint(points[i + 4], points[j + 4]), rota, Vector3D::one);
		trsCylinderR = Reverse(trsCylinder);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * (Vector4D)points[i + 4], trsCylinderR * (Vector4D)points[j + 4], radiusScaled, posCol, globalMatrixOfBox * trsCylinder))
		{
			col = true;
		}
		posCol = trsCylinder * (Vector4D)posCol;
		sol = new GameObject(posCol, Vector3D::zero, Vector3D::one * 0.1f, "cube.obj", "black.png");

		int k2 = j + 6;
		if (i == 1)
			k2 = 4;

		trsCylinder = TRS(MidPoint(points[i + 6], points[k2]), rota, Vector3D::one);
		trsCylinderR = Reverse(trsCylinder);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * Vector4D(points[i + 6]), trsCylinderR * Vector4D(points[k2]), radiusScaled, posCol, globalMatrixOfBox * trsCylinder))
		{
			col = true;
		}
		posCol = trsCylinder * (Vector4D)posCol;
		sol = new GameObject(posCol, Vector3D::zero, Vector3D::one * 0.1f, "cube.obj", "black.png");
	}

	//cylinder vertical

	for (int i = 0; i < 4; ++i)
	{
		Matrix4x4 trsCylinder = TRS(MidPoint(points[i], points[i + 4]), {0,90,0}, Vector3D::one);
		Matrix4x4 trsCylinderR = Reverse(trsCylinder);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * Vector4D(points[i]), trsCylinderR * Vector4D(points[i+4]), radiusScaled, posCol, globalMatrixOfBox * trsCylinder))
		{
			col = true;
		}
		posCol = trsCylinder * (Vector4D)posCol;
		GameObject* sol = new GameObject(posCol, Vector3D::zero, Vector3D::one * 0.1f, "cube.obj", "shield.png");
	}

	return col;
}

bool CollisionSegmentCylinder(Vector3D startSeg, Vector3D endSeg, Vector3D startEdge, Vector3D endEdge, float radius, Vector3D& posCol, Matrix4x4 worldTransform)
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

		Vector3D worldPosCol = worldTransform * Vector4D(posCol);
		Vector3D worldstartSeg = worldTransform * Vector4D(startSeg);
		Vector3D worldNewPosCol = worldTransform * Vector4D(startSeg + AB * t0);

		if (Norm(worldPosCol - worldstartSeg) > Norm(worldNewPosCol - worldstartSeg))
			posCol = startSeg + AB * t0;

		return true;
	}
	
	return false;
}