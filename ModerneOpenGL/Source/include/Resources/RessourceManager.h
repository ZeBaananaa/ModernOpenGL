#pragma once

__interface IRessource
{

};

#include <raylib.h>
#include <string>
#include <map>
class AssetManager
{
public:
	~AssetManager();

	static AssetManager& GetInstance();
	static void Destroy();
	TestRessource*tex = GetTexture(std::string name);
	TestRessource* tex = ressorceManager.Create<TestRessource>("titi.jpg");
private:
	std::map<std::string, Music> musics;
	std::map<std::string, Sound> sounds;
	std::map<std::string, Texture2D> textures;

	static AssetManager* instance;
	AssetManager();
};