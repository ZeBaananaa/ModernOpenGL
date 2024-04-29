#pragma once
#include <string>
#include <map>
#include "Log.h"
interface IResource
{
	virtual void Load(std::string name);
	virtual void UnLoad();
};

class Model;
class ResourceManager
{
public:
	~ResourceManager();

	static ResourceManager& Get();
	static void Destroy();

	bool IsKeyInList(std::string name);

	template <typename T>
	T* Get(std::string name)
	{
		if (IsKeyInList(name))
		{
			auto it = resources.find(name);
			return (T*)(it->second);
		}
		else
			return nullptr;
	}

	template <typename T>
	T* Create(std::string name)
	{
		std::string extension = GetExtension(name);
		T* resource = nullptr;
		
		if (CheckExtension(extension))
		{
			if (extension == ".obj")
			{
				resource = new Model(name);

				DEBUG_LOG("Does the resource " + name + " already exist ?");
				if(IsKeyInList(name))
				{
					Delete(name);
				}
				
				resources[name] = resource;
			}
		}
		
		return resource;
	};

	void Delete(std::string name);

	std::string GetExtension(std::string name);
	bool CheckExtension(std::string extension);

private:
	ResourceManager() = default;
	static ResourceManager* instance;

	std::map<std::string, IResource*> resources;

	std::string lstExtension[1] = {".obj"};
	int nbExtensionKnow = 1;
};