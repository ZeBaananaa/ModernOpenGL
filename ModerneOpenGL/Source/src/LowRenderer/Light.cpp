#include "Light.h"
#include "Log.h"

void LightManager::SetLight(DirectionalLights lightToSet, Vector4D direction, Vector4D ambientColor, Vector4D diffuseColor, Vector4D specularColor, bool enable)
{
	int index = static_cast<int>(lightToSet);

	directional[index].lightDirection = direction;

	directional[index].lightAmbientColor = ambientColor;
	directional[index].lightDiffuseColor = diffuseColor;
	directional[index].lightSpecularColor = specularColor;

	directional[index].enable = enable;
}

void LightManager::SetLight(PointLigths lightToSet, Vector4D position, Vector4D ambientColor, Vector4D diffuseColor, Vector4D specularColor, float constant, float linear, float quadratic, bool enable)
{
	int index = static_cast<int>(lightToSet);

	points[index].lightPosition = position;

	points[index].lightAmbientColor = ambientColor;
	points[index].lightDiffuseColor = diffuseColor;
	points[index].lightSpecularColor = specularColor;

	points[index].constant = constant;
	points[index].linear = linear;
	points[index].quadratic = quadratic;

	points[index].enable = enable;
}

void LightManager::SetLight(SpotLights lightToSet, Vector4D position, Vector4D direction, Vector4D ambientColor, Vector4D diffuseColor, Vector4D specularColor, float cutOff, float outerCutOff, bool enable)
{
	int index = static_cast<int>(lightToSet);

	spots[index].lightPosition = position;
	spots[index].lightDirection = direction;

	spots[index].lightAmbientColor = ambientColor;
	spots[index].lightDiffuseColor = diffuseColor;
	spots[index].lightSpecularColor = specularColor;

	spots[index].cutOff = cosf(cutOff * PI/180.f);

	spots[index].outerCutOff = cosf(outerCutOff * PI / 180.f);

	spots[index].enable = enable;
}

void LightManager::SetActive(DirectionalLights lightToSet, bool enable)
{
	directional[static_cast<int>(lightToSet)].enable = enable;
}

void LightManager::SetActive(PointLigths lightToSet, bool enable)
{
	points[static_cast<int>(lightToSet)].enable = enable;
}

void LightManager::SetActive(SpotLights lightToSet, bool enable)
{
	spots[static_cast<int>(lightToSet)].enable = enable;
}

void LightManager::SetSpotAngle(SpotLights lightToSet, float angleInDegree, bool add)
{
	float e = GetSpotAngle(lightToSet) - (acosf(spots[static_cast<int>(lightToSet)].outerCutOff) * 180.f/PI);

	if(add)
	{
		spots[static_cast<int>(lightToSet)].cutOff -= angleInDegree * PI / 180.f;
	}
	else
		spots[static_cast<int>(lightToSet)].cutOff = cosf(angleInDegree * PI / 180.f);

	if(spots[static_cast<int>(lightToSet)].cutOff >= 1)
	{
		spots[static_cast<int>(lightToSet)].cutOff = cosf(2.f * PI / 180.f);
	}
	else if (spots[static_cast<int>(lightToSet)].cutOff <= 0)
	{
		spots[static_cast<int>(lightToSet)].cutOff = cosf(90.f * PI / 180.f);
	}

	spots[static_cast<int>(lightToSet)].outerCutOff = cosf((GetSpotAngle(lightToSet) - e) * PI / 180.f);
}

void LightManager::SetSpotOuterCutOff(SpotLights lightToSet, float angleInDegree)
{
	float currentCutOff = GetSpotAngle(lightToSet);
	if (angleInDegree >= currentCutOff)
	{
		angleInDegree = currentCutOff - 1.f;
	}
	if (angleInDegree < 1)
		angleInDegree = 1;
	
	spots[static_cast<int>(lightToSet)].outerCutOff = cosf(angleInDegree * PI / 180.f);
}

float LightManager::GetSpotAngle(SpotLights lightToSet)
{
	return acosf(spots[static_cast<int>(lightToSet)].cutOff) * 180/PI;
}

void LightManager::SetUpDirectional()
{
	for (size_t i = 0; i < 4; i++)
	{
		directional[i] = DirectionalLight();

		directional[i].lightColor			= { 1,1,1,1 };

		directional[i].lightDirection		= { 0,-1,0,0 };

		directional[i].lightAmbientColor	= { 0.8,0.8,0.8,1 };
		directional[i].lightDiffuseColor	= { 0,0,0,1 };
		directional[i].lightSpecularColor	= { 0.5,0.5,0.5,1 };

		directional[i].enable = false;
	}
}

void LightManager::SetUpPoints()
{
	for (size_t i = 0; i < 4; i++)
	{
		points[i] = PointLight();

		points[i].lightColor		= { 1,1,1,1 };

		points[i].lightPosition		= { 0,0,0,1 };

		points[i].lightAmbientColor	= { 0,0,0,1 };
		points[i].lightDiffuseColor	= { 0.8f,0.8f,0.8f,1 };
		points[i].lightSpecularColor= { 1,1,1,1 };

		points[i].constant		= 1.f;
		points[i].linear		= 0.4f;
		points[i].quadratic		= 0.4f;

		points[i].enable = false;
	}
}

void LightManager::SetUpSpots()
{	
	for (size_t i = 0; i < 4; i++)
	{
		spots[i] = SpotLight();

		spots[i].lightColor			= { 1,1,1,1 };

		spots[i].lightPosition		= { 0,0,0,1 };
		spots[i].lightDirection		= { 0,-1,0,0 };

		spots[i].lightAmbientColor	= { 0,0,0,1 };
		spots[i].lightDiffuseColor	= { 0.8f,0.8f,0.8f,1 };
		spots[i].lightSpecularColor	= { 1,1,1,1 };

		spots[i].cutOff			= cosf(45.f * PI / 180.f);
		spots[i].outerCutOff	= cosf(30.f * PI / 180.f);

		spots[i].enable = false;
	}
}

void LightManager::Init()
{
	SetUpDirectional();
	SetUpPoints();
	SetUpSpots();

	SetLight(DirectionalLights::DIR0, { 1,-1,-1,0 }, { 10,10,10,1.f }, { 0,0,0,1 }, { 0.5f,0.5f,0.5f,1 }, true);

	SetLight(PointLigths::PT0, { 5,5,2,1 }, { 0,0,0,1 }, { 7,7,7,1 }, { 2,2,2,1 }, 1, 0.4, 0.4, true);

	SetLight(SpotLights::SP0, { 0,0,5,1 }, { 0,0,-1,0 }, { 1,1,1,1 }, { 15,15,15,1 }, { 0.2f,0.2f,0.2f,1.f }, 45 , 30 , true);
}
