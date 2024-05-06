#pragma once
#include "MathPerso.h"

struct DirectionalLight
{
	Vector4D lightDirection;

	Vector4D lightAmbientColor;
	Vector4D lightDiffuseColor;
	Vector4D lightSpecularColor;

	float constant;
	float linear;
	float quadratic;
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

	float constant;
	float linear;
	float quadratic;
	float cutoff;
	float outerCutOff;

	GLuint ubo;
};