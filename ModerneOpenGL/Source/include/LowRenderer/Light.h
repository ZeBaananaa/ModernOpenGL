#pragma once
#include "glad/glad.h"
#include "MathPerso.h"
enum class DirectionalLights
{
	DIR0,
	DIR1,
	DIR2,
	DIR3,
	NbLight
};

enum class PointLigths
{
	PT0,
	PT1,
	PT2,
	PT3,
	NbLight
};

enum class SpotLights
{
	SP0,
	SP1,
	SP2,
	SP3,
	NbLight
};

struct DirectionalLight
{
	Vector4D lightColor;

	Vector4D lightDirection;

	Vector4D lightAmbientColor;
	Vector4D lightDiffuseColor;
	Vector4D lightSpecularColor;

	int enable;
	int filling1;
	int filling2;
	int filling3;
};

struct PointLight
{
	Vector4D lightColor;

	Vector4D lightPosition;

	Vector4D lightAmbientColor;
	Vector4D lightDiffuseColor;
	Vector4D lightSpecularColor;

	float constant;
	float linear;
	float quadratic;
	int enable;
};

struct SpotLight
{
	//rgba
	Vector4D lightColor;

	Vector4D lightPosition;
	Vector4D lightDirection;

	Vector4D lightAmbientColor;
	Vector4D lightDiffuseColor;
	Vector4D lightSpecularColor;


	float cutOff;
	float outerCutOff;
	int enable;
	int filling3;
};


struct LightManager
{
	DirectionalLight directional[4];
	PointLight points[4];
	SpotLight spots[4];

	GLuint ubo;
	float filling1;
	float filling2;
	float filling3;

	void SetLight(DirectionalLights lightToSet, Vector4D direction, Vector4D ambientColor,Vector4D diffuseColor,Vector4D specularColor,bool enable);
	void SetLight(PointLigths lightToSet, Vector4D position, Vector4D ambientColor, Vector4D diffuseColor, Vector4D specularColor
		, float constant, float linear, float quadratic, bool enable);
	void SetLight(SpotLights lightToSet, Vector4D position, Vector4D direction, Vector4D ambientColor, Vector4D diffuseColor, Vector4D specularColor
		, float cutOff, float outerCutOff, bool enable);

	void SetActive(DirectionalLights lightToSet, bool enable);
	void SetActive(PointLigths lightToSet, bool enable);
	void SetActive(SpotLights lightToSet, bool enable);


	void SetUpDirectional();
	void SetUpPoints();
	void SetUpSpots();
	void Init();
};