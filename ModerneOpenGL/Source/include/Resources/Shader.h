#pragma once
#include "ResourcesManager.h"

class Shader : public IResource
{
	Shader();
	~Shader();

	bool SetVertexShader(std::filesystem::path const& filename);
	bool SetFragmentShader(std::filesystem::path const& filename);
	bool Link();

};