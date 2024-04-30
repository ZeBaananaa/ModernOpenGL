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