#include "App.h"

    bool Application::Initialise()
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

    void Application::Terminate()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void Application::Update()
    {
        Render();
    }

    void Application::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_VAO);

        //draw arrays ou elements
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    }