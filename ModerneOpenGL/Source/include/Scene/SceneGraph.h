#pragma once
#include "Transform.h"

class SceneGraph
{
public:
	static SceneGraph& Get();
	static void Destroy();
	~SceneGraph();

	Transform* root;

	void Update();
	void Render();

private:
	SceneGraph();
	static SceneGraph* instance;
};