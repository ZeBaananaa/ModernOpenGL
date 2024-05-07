#include "Light.h"

void LightManager::SetUpDirectional()
{
	
	for (size_t i = 0; i < 4; i++)
	{
		directional[i] = DirectionalLight();

		directional[i].lightColor			= { 1,1,1,1 };

		directional[i].lightDirection		= { 0,-1,0,0 };

		directional[i].lightAmbientColor	= { 1,1,1,1 };
		directional[i].lightDiffuseColor	= { 0,0,0,1 };
		directional[i].lightSpecularColor	= { 1,1,1,1 };

		directional[i].enable = false;
	}
}

void LightManager::SetUpPoints()
{
	
	for (size_t i = 0; i < 4; i++)
	{
		points[i] = PointLight();

		points[i].lightColor			= { 1,1,1,1 };

		points[i].lightPosition		= { 0,0,0,1 };

		points[i].lightAmbientColor	= { 0,0,0,1 };
		points[i].lightDiffuseColor	= { 1,1,1,1 };
		points[i].lightSpecularColor	= { 1,1,1,1 };

		points[i].constant		= 1.f;
		points[i].linear		= 0.4f;
		points[i].quadratic	= 0.4f;

		points[i].enable = false;
	}
}

void LightManager::SetUpSpots()
{
	
	for (size_t i = 0; i < 4; i++)
	{
		spots[i] = SpotLight();

		spots[i].lightColor			= { 1,1,1,1 };

		spots[i].lightPosition			= { 0,0,0,1 };
		spots[i].lightDirection		= { 0,-1,0,0 };

		spots[i].lightAmbientColor		= { 0,0,0,1 };
		spots[i].lightDiffuseColor		= { 1,1,1,1 };
		spots[i].lightSpecularColor	= { 1,1,1,1 };

		spots[i].constant	= 1.f;
		spots[i].linear	= 0.4f;
		spots[i].quadratic = 0.4f;

		spots[i].enable = false;

		spots[i].cutoff		= 30.f;
		spots[i].outerCutOff	= 0.f;
	}
}

void LightManager::Init()
{
	SetUpDirectional();
	SetUpPoints();
	SetUpSpots();

	colorTest = { 1,1,1,1 };
	
	//directional[0].enable = true;
}

void LightManager::Destroy()
{
	//delete[] directional;
	//delete[] points;
	//delete[] spots;
}
