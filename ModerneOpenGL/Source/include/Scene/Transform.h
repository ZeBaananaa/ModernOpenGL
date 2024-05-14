#pragma once
#include "MathPerso.h"
#include <vector>

class GameObject;
class Transform
{
public:
	Transform(bool root = false);
	Transform(GameObject* _gameObject);
	Transform(GameObject* _gameObject,Transform* _parent);
	Transform(Vector3D position,Vector3D rotation,Vector3D scale,GameObject* _gameObject, Transform* _parent);
	~Transform();
	void SetZero();

	void Update();
	void Render();
	void Delete();

	void SetParent(Transform* parent);
	void SetChildrenRecalculateGlobalTransform();

	GameObject* gameObject = nullptr;

	#pragma region Local Get/Set
	
	Matrix4x4 GetLocalTransform();

	Vector3D GetLocalPosition();
	void SetLocalPosition(Vector3D newPosition);
	
	Vector3D GetLocalRotation();
	void SetLocalRotation(Vector3D newRotation);
	
	Vector3D GetLocalScale();
	void SetLocalScale(Vector3D newScale);
	#pragma endregion

	#pragma region Global Get

	Matrix4x4 GetGlobalTransform();

	Vector3D GetGlobalPosition();
	Vector3D GetGlobalRotation();
	Vector3D GetGlobalScale();

	#pragma endregion

	std::string GetName() const;
	void SetName(std::string value);

	std::vector<Transform*>& GetChildren();

	bool recalculateLocalT = true;
	bool recalculateGlobalT = true;

private :
	void SetLocalTransformOnParentChange();
	void AddChildren(Transform* child);
	void RemoveChildren(Transform* child);
	std::vector<Transform*> children;

	Matrix4x4 localTransform;
	Matrix4x4 globalTransform;
	
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;

	Vector3D globalPosition;
	//local rota + parent rota + parent parent rota (+ parent global rota en gros)
	Vector3D globalRotation;
	//local scale * parent local scale * ...
	Vector3D globalScale;

	Transform* parent = nullptr;
	std::string name = "";
};

