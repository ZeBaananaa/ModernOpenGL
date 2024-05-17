#include "SceneGraph.h"

SceneGraph* SceneGraph::instance = nullptr;

void SceneGraph::Update()
{
	root->Update();
}

void SceneGraph::Render()
{
	root->Render();
}

SceneGraph::SceneGraph()
{
	root = new Transform(true);
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