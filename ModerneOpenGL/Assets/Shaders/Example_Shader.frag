#version 330 core

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
	FragColor = texture(text, posIn.uvPos);
}