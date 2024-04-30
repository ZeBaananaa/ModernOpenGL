#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 color;
uniform mat4x4 MVP;
uniform mat4 normalMat; // transpose inverte MVP

out PosOut
{
    vec3 newPos;
    vec3 normalPos;
    vec2 uvPos;
} posOut;

// ligne - colonne 

void main()
{
    posOut.uvPos = uv;
    vec4 vec4Normal = vec4(normal.x, normal.y, normal.z, 1.f);
    vec4 posVec4 = vec4(pos.x, pos.y, pos.z, 1.f);
    posOut.normalPos = (normalMat * vec4Normal).xyz;
    gl_Position = (posVec4 * MVP);
    posOut.newPos = gl_Position.xyz;
}