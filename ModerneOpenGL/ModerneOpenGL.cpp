// ModerneOpenGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

//si vous utilisez gle32s.lib (et donc pas de dll)
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <cstdint>
#include "Log.h"
#include "MathPerso.h"
void testLog()
{
    Log logPerso("debug.txt");
    int leInt = 5;
    logPerso.Print("hello world %d %d", leInt, leInt + 1);
    float leFloat = 4.0f;
    logPerso.Print("hello world %f", leFloat);
    Vector4D v(1.f, 2.f, 3.f, 4.f);
    logPerso.Print(v.ToString());

    DEBUG_LOG("ayoo %g", 5));
}

int main()
{
    testLog();
    return 0;
}

//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    //init extension
//    GLenum error = glewInit();
// 
//    Application app;
//    app.Initialise();
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//
//        /* Render here */
//        app.Update();
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    app.Terminate();
//    glfwTerminate();
//    return 0;
//}
