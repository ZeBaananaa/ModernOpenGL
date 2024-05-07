#pragma once
#include <glad/glad.h>
#include <gl/GL.h>

#include "ResourcesManager.h"

#define STB_IMAGE_IMPLEMENTATION

class Texture : public IResource
{
public:
	Texture() = default;
	Texture(std::string filename, GLuint mode = GL_REPEAT);
	~Texture();

	void SetAnisotropy(float value);
	void SetMode(GLuint value);
	GLuint GetMode() const;
	float GetAnisotropy() const;
	float GetMaxAnisotropy() const;

	void Bind();
	void Unbind();
	

private:
	void UnLoad() override;
	void Load(std::string filename) override;
	void LoadTextureFlag(GLuint param = GL_REPEAT);

private:
	unsigned char* data;
	unsigned int texture;
	int width, height, nrChannels;

	GLuint mode;
	float anisotropy;
	float maxAnisotropy;
};