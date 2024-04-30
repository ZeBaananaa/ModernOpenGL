#include "GameObject.h"

Transform::Transform(bool root)
{
	gameObject = nullptr;
	if(!root)
		SceneGraph::Get().root->AddChildren(this);
}

Transform::Transform(GameObject* _gameObject)
{
	gameObject = _gameObject;
	SceneGraph::Get().root->AddChildren(this);
}

Transform::Transform(GameObject* _gameObject, Transform* _parent)
{
	gameObject = _gameObject;
	if(_parent)
		_parent->AddChildren(this);
	else
		SceneGraph::Get().root->AddChildren(this);
}


Transform::~Transform()
{
	delete gameObject;
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->Delete();
	}
	children.clear();
}

void Transform::Update()
{
	gameObject->Update();

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->gameObject->Update();
	}
}

void Transform::Delete()
{
	delete this;
}


void Transform::SetParent(Transform* _parent)
{
	if (parent != nullptr)
	{
		parent->RemoveChildren(this);
	}
	parent = _parent;

	if (parent == nullptr)
		parent = SceneGraph::Get().root;
	
	parent->AddChildren(this);
}

void Transform::AddChildren(Transform* child)
{
	if (child == nullptr)
		return;

	children.push_back(child);
}

void Transform::RemoveChildren(Transform* child)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i] == child)
		{
			children[i]->parent = nullptr;
			children.erase(children.begin() + i);
			return;
		}
	}
}


Matrix4x4 Transform::GetLocalTransform()
{
	if (recalculateLocalT)
	{
		recalculateLocalT = false;
		localTransform = TRS(localPosition,localRotation,localScale);
	}
	
	return localTransform;
}

Matrix4x4 Transform::GetGlobalTransform()
{
	if (parent == nullptr)
		return localTransform;

	if (recalculateLocalT)
	{
		GetLocalTransform();
	}
	if (recalculateGlobalT)
	{
		recalculateGlobalT = false;
		globalTransform = parent->GetGlobalTransform() * localTransform;
	}

	return globalTransform;
}


Vector3D Transform::GetGlobalPosition()
{
	return GetGlobalTransform() * static_cast<Vector4D>(localPosition);
}

Vector3D Transform::GetLocalPosition()
{
	return localPosition;
}

void Transform::SetLocalPosition(Vector3D newPosition)
{
	localPosition = newPosition;
	recalculateLocalT = true;

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->recalculateGlobalT = true;
	}
}

Vector3D Transform::GetLocalRotation()
{
	return localRotation;
}

void Transform::SetLocalRotation(Vector3D newRotation)
{
	localRotation = newRotation;
	recalculateLocalT = true;

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->recalculateGlobalT = true;
	}
}

Vector3D Transform::GetLocalScale()
{
	return localScale;
}

void Transform::SetLocalScale(Vector3D newScale)
{
	localScale = newScale;
	recalculateLocalT = true;

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->recalculateGlobalT = true;
	}
}