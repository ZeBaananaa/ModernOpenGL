#include "Mesh.h"


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	if (model)
	{
		delete model;
		model = nullptr;
	}
	
}