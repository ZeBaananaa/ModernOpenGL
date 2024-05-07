#pragma once
#include "glad/glad.h"

struct vec4
{
	float x;
	float y; 
	float z; 
	float w;
};

struct DirectionalLight
{
	vec4 lightColor;

	vec4 lightDirection;

	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;

	int enable;
	int filling1;
	int filling2;
	int filling3;
	//vec4 ConstLinQuadOnOFF; // {constant,linear,quadratic,true/false}

};

struct Test
{
	vec4 colorTest2;
};
struct PointLight
{
	vec4 lightColor;

	vec4 lightPosition;

	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;

	float constant;
	float linear;
	float quadratic;
	int enable;
};

struct SpotLight
{
	//rgba
	vec4 lightColor;

	vec4 lightPosition;
	vec4 lightDirection;

	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;

	//vec4 ConstLinQuadOnOFF;
	float constant;
	float linear;
	float quadratic;
	int enable;

	float cutoff;
	float outerCutOff;
	float filling2;
	float filling3;
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

	void SetUpDirectional();
	void SetUpPoints();
	void SetUpSpots();
	void Init();
	void Destroy();
};