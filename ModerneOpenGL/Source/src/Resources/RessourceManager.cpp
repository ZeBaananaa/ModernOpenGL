#include "RessourceManager.h"

class RessourceManager
{
public:
	RessourceManager();
	~RessourceManager();

private:

};

RessourceManager::RessourceManager()
{
}

RessourceManager::~RessourceManager()
{
}

RessourceManager& RessourceManager::GetInstance()
{
	if (instance == nullptr)
		instance = new AssetManager();
	return *instance;
}
