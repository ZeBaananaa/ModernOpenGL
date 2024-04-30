#pragma once

#include "ResourcesManager.h"

class Shader : public IResource
{
public:
	Shader();
	~Shader();

	bool SetVertexShader(std::filesystem::path const& filename);
	bool SetFragmentShader(std::filesystem::path const& filename);
	bool Link();

private:
	int vertexShader;
	int fragmentShader;
	int shaderProgram;
};