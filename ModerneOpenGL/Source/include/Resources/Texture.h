#pragma once
#include "ResourcesManager.h"

uint32_t mipLevels;
VkImage textureImage;

class  Textures : public IResource
{
public:
	Textures(std::filesystem::path const& filename);

};


