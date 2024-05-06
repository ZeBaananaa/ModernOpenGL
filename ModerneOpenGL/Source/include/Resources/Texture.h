#pragma once
#include <glad/glad.h>
#include <gl/GL.h>

#include "ResourcesManager.h"

#define STB_IMAGE_IMPLEMENTATION

class Texture : public IResource
{
public:
	Texture() = default;
	Texture(std::string filename);
	~Texture() = default;

	void Load(std::string filename) override;

	void Bind();
	void Unbind();

private:
	unsigned char* data;
	unsigned int texture;
	int width, height, nrChannels;
};