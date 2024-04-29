#include "Shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{
}

bool Shader::SetVertexShader(std::filesystem::path const& filename)
{
	try
	{
		return true;
	}
	catch (const std::exception&)
	{
		DEBUG_LOG("Vertex shader could not load properly...\nAborting...");
		return false;
	}
}

bool Shader::SetFragmentShader(std::filesystem::path const& filename)
{
	try
	{
		return true;
	}
	catch (const std::exception&)
	{
		DEBUG_LOG("Fragment shader could not load properly...\nAborting...");
		return false;
	}
}

bool Shader::Link()
{
	try
	{
		return true;
	}
	catch (const std::exception&)
	{
		DEBUG_LOG("Shader could not be linked to program...\nAborting...");
		return false;
	}
}
