// ModerneOpenGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

//si vous utilisez gle32s.lib (et donc pas de dll)
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdint>

#ifdef NDEBUG
#define Assert(x) if(x == false){abort();}
#else
#define Assert(x) if(x == false){__debugbreak();}
#endif



struct vec2 { float x, y; }; // ou r,g ou s,t
struct vec3 { float x, y, z; }; // ou r,g,b ou s,t,p
struct vec4 { float x, y, z, w; }; // ou r,g,b,a ou s,t,p,q
bool on = true;


struct Vertex
{
    //attributte du sommet
    vec2 position;
    vec3 color;

};

Vertex g_Triangles[] = {    Vertex{{-0.5f,-0.5f},   {1.f,0.f,0.f}},
                            Vertex{{0.5f,-0.5f},    {0.f,1.f,0.f}},
                            Vertex{{0.f,0.5f},      {0.f,0.f,1.f}} 
                        };

Vertex sablier[] = {    g_Triangles[0],     g_Triangles[1],    g_Triangles[2],

                    Vertex{{-0.5f,1.f},   {1.f,0.f,0.f}},
                    Vertex{{0.5f,1.f},    {0.f,1.f,0.f}},
                    Vertex{{0.f,0.25f},      {0.f,0.f,1.f}}
};

uint16_t g_Indices[] = { 0,1,2 };

uint16_t g_IndicesSablier[] = { 0,1,5,4,3,5 };

class Application
{
public:
   // Application();
    //~Application();

    int32_t m_width = 1280;
    int32_t m_height = 720;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    GLuint m_VAO = 0;


    bool Initialise()
    {
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
        glGenVertexArrays(1, &m_VAO);

        glBindVertexArray(m_VAO);
        // array car utilise par glDrawArrays()
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        //if data == null juste alloue memoire
        //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, g_Triangles, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, sablier, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 3, g_Indices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, g_IndicesSablier, GL_STATIC_DRAW);

        #define POSITION 0
        #define COLOR 3
        // indice vbo si plusieur vbo (pos,couleur,ect.) ici tout dans 1 /nbcomposants/type composants/noramaliser?/size of struct
        //pos
        glVertexAttribPointer(POSITION, 2, GL_FLOAT, false, sizeof(Vertex),(void*)offsetof(Vertex,position));
        glEnableVertexAttribArray(POSITION);
        //color
        glVertexAttribPointer(COLOR, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(COLOR);

        #undef POSITION
        #undef COLOR

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        return true;
    }

    void Terminate()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void Update()
    {
        Render();
    }

    void Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_VAO);

        //draw arrays ou elements
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    }
};




int main(void)
{
    GLFWwindow* window;
    
    Assert(on);
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //init extension
    GLenum error = glewInit();
 
    Application app;
    app.Initialise();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        app.Update();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    app.Terminate();
    glfwTerminate();
    return 0;
}

