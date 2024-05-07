#version 330 core

uniform vec3 viewPos;

in VertexOut
{
    vec3 fragPos;
    vec3 normalPos;
    vec2 uvPos;
    vec4 fragColor;
} vertexIn;

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
	vec4 lightColor;

	vec4 lightPosition;
	vec4 lightDirection;

	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;

	float constant;
	float linear;
	float quadratic;
	int enable;

	float cutoff;
	float outerCutOff;
	float filling2;
	float filling3;
};

layout (std140) uniform Lights
{
	DirectionalLight directionalLights[4];
	PointLight pointsLights[4];
	SpotLight spotsLights[4];
	
	
	uint ubo;
	float filling1;
	float filling2;
	float filling3;

};

out vec4 FragColor;
in PosOut
{
    vec3 newPos;
    vec3 normalPos;
    vec2 uvPos;
} posIn;

uniform sampler2D text;

void main()
{
	vec4 textColor = texture(text, posIn.uvPos);

	vec3 result = vec3(textColor);
	
//	for(int i=0;i<4;i++)
//	{
//		if(directionalLights[i].enable == 1)
//		{
//			DirectionalLight dir = directionalLights[i];
//
//			//ambient
//			vec3 ambient =  vec3(dir.lightAmbientColor) * vec3(1,1,1);
//	
//			//diffuse
//			vec3 norm = normalize(vertexIn.normalPos);
//			vec3 lightDir = normalize(vec3(-dir.lightDirection));//vec3(u_Position) - vertexIn.fragPos);
//
//			float diff = max(dot(norm,lightDir),0.0);
//			vec3 diffuse = vec3(1,1,1)*diff;
//
//			//specular
//			vec3 viewDir = normalize(viewPos - vertexIn.fragPos);
//			vec3 reflectDir = reflect(-lightDir,norm);
//
//			float spec = pow(max(dot(viewDir,reflectDir),0.0),1.f);//shininess);
//			vec3 specular = vec3(dir.lightSpecularColor) * spec * vec3(1,1,1);
//
//			//float dist = length(u_Position.xyz - fragPos);
//			//float attenuation = 1.0/(u_Constant+u_Linear*dist+u_Quadratic*dist*dist);
//			//vec3 halfwayDir = normalize(lightDir+viewDir);
//
//			result = (ambient + diffuse + specular) * result;
//		}
//	}
	FragColor = vec4(result,1.0);
}