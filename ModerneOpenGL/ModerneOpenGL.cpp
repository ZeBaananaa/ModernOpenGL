// ModerneOpenGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.


#include "Assertion.h"
//#include <cstdint>
#include "Log.h"
#include "MathPerso.h"
#include "App.h"
#include "InputHandler.h"

#include <glad/glad.h>
#include <iostream>

int Init()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return - 1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Modern OpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Cannot create GLFW Window... \nAborting!" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Init glad after context is defined */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, InputHandler::KeyCallback);

    Application app;
    app.Initialise();

    // Set background color to blue
    glClearColor(0.15f, 0.15f, 1.f, 1.f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        app.Update();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        if (InputHandler::IsKeyPressed(GLFW_KEY_SPACE))
            std::cout << "Key Pressed" << std::endl;

        if (InputHandler::IsKeyDown(GLFW_KEY_SPACE))
            std::cout << "Key Down" << std::endl;

        if (InputHandler::IsKeyReleased(GLFW_KEY_SPACE))
            std::cout << "Key Released" << std::endl;

        /* Poll for and process events */
        glfwPollEvents();
    }

    app.Terminate();
    glfwTerminate();
    return 0;
}

int main()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Init();

    Log::Get().Destroy();

    return 0;
}