#version 410 core

in layout (location = 0) vec3 pos;
in layout (location = 1) vec2 uv;
in layout (location = 2) vec3 normal;
in layout (location = 3) vec3 color;
uniform mat4x4 MVP;
uniform mat4 normalMat; // transpose inverte MVP

out PosOut
{
    vec3 newPos;
    vec3 normalPos;
    vec2 uvPos;
} posOut;

out vec3 colorOut;
// ligne - colonne 

void main()
{
    posOut.uvPos = uv;
    vec4 vec4Normal = vec4(normal.x, normal.y, normal.z, 1.f);
    vec4 posVec4 = vec4(pos.x, pos.y, pos.z, 1.f);
    posOut.normalPos = (normalMat * vec4Normal).xyz;
    gl_Position = (posVec4);
    posOut.newPos = gl_Position.xyz;
    colorOut = vec3(1.f, 1.f, 1.f);
}