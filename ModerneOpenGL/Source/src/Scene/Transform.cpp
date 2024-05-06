#include "GameObject.h"

Transform::Transform(bool isRoot)
{
	gameObject = nullptr;

	if(!isRoot)
		SetParent(SceneGraph::Get().root);

	SetZero();
}

Transform::Transform(GameObject* _gameObject)
{
	if (_gameObject)
		gameObject = _gameObject;
	
	SetParent(SceneGraph::Get().root);

	SetZero();
}

Transform::Transform(GameObject* _gameObject, Transform* _parent)
{
	if (_gameObject)
		gameObject = _gameObject;

	if (_parent)
		SetParent(_parent);
	else
		SetParent(SceneGraph::Get().root);

	SetZero();
}

Transform::Transform(Vector3D position, Vector3D rotation, Vector3D scale, GameObject* _gameObject, Transform* _parent)
{

	if (_gameObject)
		gameObject = _gameObject;

	if (_parent)
		SetParent(_parent);
	else
		SetParent(SceneGraph::Get().root);


	localPosition = position;
	localRotation = rotation;
	localScale = scale;

	recalculateLocalT = true;
	GetLocalTransform();
	GetGlobalTransform();
}


Transform::~Transform()
{
	if(gameObject != nullptr)
		delete gameObject;

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->Delete();
		--i;
	}

	if (parent)
		parent->RemoveChildren(this);
	children.clear();
}

void Transform::SetZero()
{
	localPosition = Vector3D::zero;
	localRotation = Vector3D::zero;
	localScale = Vector3D::one;

	localTransform = Identity_Matrix4x4();
	globalTransform = Identity_Matrix4x4();
}



void Transform::Update()
{
	if(gameObject)
		gameObject->Update();

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->gameObject->Update();
	}
}

void Transform::Render()
{
	if (gameObject)
	{
		MeshRenderer* mesh = gameObject->GetComponent<MeshRenderer>();
		if (mesh)
			mesh->Update();
	}
		

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->gameObject->transform->Render();
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

	SetLocalTransformOnParentChange();
}

void Transform::SetChildrenRecalculateGlobalTransform()
{
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->recalculateGlobalT = true;
		children[i]->SetChildrenRecalculateGlobalTransform();
	}
}

void Transform::AddChildren(Transform* child)
{
	if (child == nullptr)
		return;

	child->recalculateGlobalT = true;

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

#pragma region Local Transform

void Transform::SetLocalTransformOnParentChange()
{
	//check if every thing is up to date
	recalculateGlobalT = false;

	Matrix4x4 reverseParentRotation_G = Reverse(Rotation_Matrix4x4(parent->GetGlobalRotation()));
	Matrix4x4 reverseParentScale_G = Reverse(Scaling_Matrix4x4(parent->GetGlobalScale()));

	localRotation = reverseParentRotation_G * static_cast<Vector4D>(GetGlobalRotation());
	localScale = reverseParentScale_G * static_cast<Vector4D>(GetGlobalScale());
	localPosition = reverseParentScale_G * reverseParentRotation_G * static_cast<Vector4D>(GetGlobalPosition() - parent->GetGlobalPosition());

	recalculateLocalT = true;
	GetLocalTransform();
	GetGlobalTransform();

	SetChildrenRecalculateGlobalTransform();
}

Matrix4x4 Transform::GetLocalTransform()
{
	if (recalculateLocalT)
	{
		recalculateLocalT = false;
		recalculateGlobalT = true;
		localTransform = TRS(localPosition,localRotation,localScale);
	}
	
	return localTransform;
}

Vector3D Transform::GetLocalPosition()
{
	return localPosition;
}

void Transform::SetLocalPosition(Vector3D newPosition)
{
	localPosition = newPosition;
	recalculateLocalT = true;

	SetChildrenRecalculateGlobalTransform();
}

Vector3D Transform::GetLocalRotation()
{
	return localRotation;
}

void Transform::SetLocalRotation(Vector3D newRotation)
{
	localRotation = newRotation;
	recalculateLocalT = true;

	SetChildrenRecalculateGlobalTransform();
}

Vector3D Transform::GetLocalScale()
{
	return localScale;
}

void Transform::SetLocalScale(Vector3D newScale)
{
	localScale = newScale;
	recalculateLocalT = true;

	SetChildrenRecalculateGlobalTransform();
}
#pragma endregion

#pragma region Global Transform

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

		GetGlobalPosition();
		GetGlobalRotation();
		GetGlobalScale();
	}

	return globalTransform;
}

Vector3D Transform::GetGlobalPosition()
{
	globalPosition = GetGlobalTransform().col4;
	return globalPosition;
}

Vector3D Transform::GetGlobalRotation()
{
	if (parent == nullptr)
		return localRotation;

	globalRotation = localRotation + parent->GetGlobalRotation();
	return globalRotation;
}

Vector3D Transform::GetGlobalScale()
{
	if (parent == nullptr)
		return localScale;

	globalScale = TensorialProduct(localScale,parent->GetGlobalScale());
	return globalScale;
}
#pragma endregion





