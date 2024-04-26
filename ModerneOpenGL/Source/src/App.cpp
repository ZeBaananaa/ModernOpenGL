#include "App.h"
#include "Model.h"

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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 3, g_Indices, GL_STATIC_DRAW);


#define POSITION 0
#define NORMAL 3
#define Texture 4
    // indice vbo si plusieur vbo (pos,couleur,ect.) ici tout dans 1 /nbcomposants/type composants/noramaliser?/size of struct
  
    glVertexAttribPointer(POSITION, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(POSITION);

    glVertexAttribPointer(NORMAL, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(NORMAL);

    glVertexAttribPointer(Texture, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, textureUV));
    glEnableVertexAttribArray(Texture);

#undef POSITION
#undef NORMAL
#undef Texture

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