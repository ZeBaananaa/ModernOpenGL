#pragma once
#include "Transform.h"

class SceneGraph
{
public:
	static SceneGraph& Get();
	static void Destroy();
	~SceneGraph();

	Transform* root;

private:
	SceneGraph();
	static SceneGraph* instance;
};

SceneGraph::SceneGraph()
{
	root->localTransform = Identity_Matrix4x4();
	root->globalTransform = root->localTransform = Identity_Matrix4x4();
}

SceneGraph& SceneGraph::Get()
{
	if (instance == nullptr)
		instance = new SceneGraph();
	return *instance;
}

void SceneGraph::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

SceneGraph::~SceneGraph()
{
	root->Delete();
}