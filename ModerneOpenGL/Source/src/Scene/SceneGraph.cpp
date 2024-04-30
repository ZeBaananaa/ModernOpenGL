#include "SceneGraph.h"

SceneGraph* SceneGraph::instance = nullptr;

SceneGraph::SceneGraph()
{
	root = new Transform(true);
	root->SetLocalPosition(Vector3D::origin3D);
	root->SetLocalRotation(Vector3D::origin3D);
	root->SetLocalScale({ 1.f,1.f,1.f });

	root->GetGlobalTransform();
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