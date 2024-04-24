#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct vec2 { float x, y; }; // ou r,g ou s,t
struct vec3 { float x, y, z; }; // ou r,g,b ou s,t,p
struct vec4 { float x, y, z, w; }; // ou r,g,b,a ou s,t,p,q

struct Vertex
{
	//attributte du sommet
	vec2 position;

	//float vertices[];
	//GLfloat normal[];
	//GLfloat color[];
	//vec2 uv; //coord texture

};

Vertex g_Triangles[] = {{-0.5f,-0.5f},
						{0.5f,-0.5f},	
						{0.f,0.5f} };

uint16_t g_Indices[] = { 0,1,2 };

// VBO 1/ save pos,color normal des sommets
// EBO 2/ indice des sommets
// VAO 3/ met tt en commun

//glgen -> gl delete		VAO gl.....VertexArrays		VBO / EBO  gl..Buffers