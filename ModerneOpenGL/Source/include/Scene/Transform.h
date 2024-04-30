#pragma once
#include "MathPerso.h"
#include <vector>
#include "IComponent.h"

class GameObject;
class Transform : public IComponent
{
public:
	Transform(bool root = false);
	Transform(GameObject* _gameObject);
	Transform(GameObject* _gameObject,Transform* _parent);
	~Transform();

	void Update() override;
	void Delete() override;

	void SetParent(Transform* parent);
	void AddChildren(Transform* child);
	void RemoveChildren(Transform* child);

	GameObject* gameObject;
	Matrix4x4 GetLocalTransform();
	Matrix4x4 GetGlobalTransform();
	Vector3D GetGlobalPosition();

	Vector3D GetLocalPosition();
	void SetLocalPosition(Vector3D newPosition);
	Vector3D GetLocalRotation();
	void SetLocalRotation(Vector3D newRotation);
	Vector3D GetLocalScale();
	void SetLocalScale(Vector3D newScale);

	bool recalculateLocalT = true;
	bool recalculateGlobalT = true;
private :
	std::vector<Transform*> children;

	Matrix4x4 localTransform;
	Matrix4x4 globalTransform;
	
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;

	Transform* parent = nullptr;
};

