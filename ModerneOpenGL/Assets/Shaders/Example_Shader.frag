#version 420 core

uniform vec3 viewPos;

in VertexOut
{
    vec3 fragPos;
    vec3 normalPos;
    vec2 uvPos;
    vec4 fragColor;
} vertexIn;

layout (std140,binding = 4) uniform SpotLight
{
	vec4  u_Color;

	vec4 u_Position;
	vec4 u_Direction;

	vec4 u_Ambient;
	vec4 u_Diffuse;
	vec4 u_Specular;

	float u_Constant;
	float u_Linear;
	float u_Quadratic;

	float u_CutOff;
	float u_OuterCutOff;

	int id;

};

//uniform int u_LightCount;
//layout (std140,binding = 5) uniform LightBlock
//{
//	SpotLight spots[u_LightCount];
//};

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
	//ambient
	vec3 ambient =  vec3(u_Ambient) * vec3(u_Color);

	//diffuse
	vec3 norm = normalize(vertexIn.normalPos);
	vec3 lightDir = normalize(vec3(u_Position) - vertexIn.fragPos);

	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = vec3(u_Color)*diff;

	//specular
	vec3 viewDir = normalize(viewPos - vertexIn.fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);

	float spec = pow(max(dot(viewDir,reflectDir),0.0),32.f);//shininess);
	vec3 specular = vec3(u_Specular) * spec * vec3(u_Color);

	//float dist = length(u_Position.xyz - fragPos);
	//float attenuation = 1.0/(u_Constant+u_Linear*dist+u_Quadratic*dist*dist);
	//vec3 halfwayDir = normalize(lightDir+viewDir);

	vec3 result = (ambient + diffuse + specular) * vec3(textColor);
	FragColor = vec4(result,1.0);
}