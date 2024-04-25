#include "Model.h"
#include <fstream>

Model::Model(std::string nameObjFile)
{
    LoadModel("Assets/Meshes/"+nameObjFile);
}

Model::~Model()
{
    vertices.clear();
    indeces.clear();
}

void Model::LoadModel(std::string nameObjFile)
{
    std::ifstream file;

    file.open(nameObjFile);
    if (!file.is_open())
    {
        printf("this file doesn't exist\n");
        return;
    }

    std::string str;
    while (str != "v" && file)
    {
        file >> str;
    }

    #pragma region GetVerteces

    std::vector<Vector3D> verticesObj;
    int indexInVector3D = 0;
    Vector3D v;

    while (str != "vt" && file)
    {
        file >> str;

        if (str[0] == 'v')
        {
            verticesObj.push_back(v);
            indexInVector3D = 0;
        }
        else
        {
            v[indexInVector3D] = std::stof(str);
            ++indexInVector3D;
        }
    }
    #pragma endregion

    #pragma region GetTextureCoords

    std::vector<Vector2D> textCoordObj;
    int indexInVector2D = 0;
    Vector2D vt;

    while (str != "vn" && file)
    {
        if (str == "vt")
        {
            textCoordObj.push_back(vt);
            indexInVector2D = 0;
        }
        else
        {
            vt[indexInVector2D] = std::stof(str);
            ++indexInVector2D;
        }

        file >> str;
    }
    #pragma endregion

    #pragma region GetNormals

    std::vector<Vector3D> normalObj;
    indexInVector3D = 0;
    Vector3D vn;

    while (str != "f" && file)
    {
        if (str == "vn")
        {
            normalObj.push_back(vn);
            indexInVector3D = 0;
        }
        else
        {
            vn[indexInVector3D] = std::stof(str);
            ++indexInVector3D;
        }

        file >> str;
    }
    #pragma endregion

    #pragma region FillVertexInfo

    Vertex vertex;
    //rdrV.r = rdrV.g = rdrV.b = rdrV.a = 1.f;
    file >> str;
    while (file)
    {
        if (str[0] != 'f')
        {
            std::string vertexInOrder;
            int i = 0;
            for (i; i < str.length(); ++i)
            {
                if (str[i] == '/')
                    break;
                else
                {
                    vertexInOrder += str[i];
                }
            }
            indeces.push_back(std::stoi(vertexInOrder) - 1);
            Vector3D currentVertexPosition = verticesObj[std::stoi(vertexInOrder) - 1];
            vertex.position.x = currentVertexPosition.x; vertex.position.y = currentVertexPosition.y; vertex.position.z = currentVertexPosition.z;

            ++i;
            std::string textCoordsInOrder;
            for (; i < str.length(); ++i)
            {
                if (str[i] == '/')
                    break;
                else
                    textCoordsInOrder += str[i];
            }
            Vector3D currentVertexUV = textCoordObj[std::stoi(textCoordsInOrder) - 1];
            vertex.textureUV.x = currentVertexUV.x; vertex.textureUV.y = currentVertexUV.y;


            ++i;
            std::string normalInOrder;
            for (; i < str.length(); ++i)
            {
                if (str[i] == '/')
                    break;
                else
                    normalInOrder += str[i];
            }
            Vector3D currentVertexNormal = textCoordObj[std::stoi(normalInOrder) - 1];
            vertex.normal.x = currentVertexNormal.x; vertex.normal.y = currentVertexNormal.y; vertex.normal.z = currentVertexNormal.z;

            vertices.push_back(vertex);
        }

        file >> str;
    }
    #pragma endregion

    file.close();
}