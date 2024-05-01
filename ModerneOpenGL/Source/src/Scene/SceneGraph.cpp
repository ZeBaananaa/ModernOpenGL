#include "SceneGraph.h"

SceneGraph* SceneGraph::instance = nullptr;

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