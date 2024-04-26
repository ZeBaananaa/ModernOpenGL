#include "Model.h"
#include <fstream>
#include <sstream>

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
    std::string line;

    std::vector<Vector3D> verticesObj;
    Vector3D v;

    std::vector<Vector2D> textCoordObj;
    Vector2D vt;

    std::vector<Vector3D> normalObj;
    Vector3D vn;

    Vertex vertex;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        iss >> str;

        if (str == "v")
        {
            for (int indexInVector3D = 0; indexInVector3D < 3; ++indexInVector3D)
            {
                iss >> str;
                v[indexInVector3D] = std::stof(str);
            }

            verticesObj.push_back(v);
        }
        else if (str == "vt")
        {
            for (int indexInVector2D = 0; indexInVector2D < 2; ++indexInVector2D)
            {
                iss >> str;
                vt[indexInVector2D] = std::stof(str);
            }

            textCoordObj.push_back(vt);
        }
        else if (str == "vn")
        {
            for (int indexInVector3D = 0; indexInVector3D < 3; ++indexInVector3D)
            {
                iss >> str;
                vn[indexInVector3D] = std::stof(str);
            }

            normalObj.push_back(vn);
        }
        else if (str == "f")
        {
            int countVertex =0;
            std::vector<Vertex> polygon;

            while (iss >> str)
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
                Vector2D currentVertexUV = textCoordObj[std::stoi(textCoordsInOrder) - 1];
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
                Vector3D currentVertexNormal = normalObj[std::stoi(normalInOrder) - 1];
                vertex.normal.x = currentVertexNormal.x; vertex.normal.y = currentVertexNormal.y; vertex.normal.z = currentVertexNormal.z;

                polygon.push_back(vertex);
                //vertices.push_back(vertex);
                ++countVertex;
            }

            for (int indexInPoly = 0; indexInPoly < polygon.size(); ++indexInPoly)
            {
                if (indexInPoly < 3)
                {
                    //sans index tab
                    vertices.push_back(polygon[indexInPoly]);
                    //indeces.push_back();
                }
                else
                {
                    vertices.push_back(polygon[0]);
                    vertices.push_back(polygon[indexInPoly-1]);
                    vertices.push_back(polygon[indexInPoly]);
                }
            }

            //if (countVertex >= 3)
            //{
            // 
            // //012
            // //023
            // //034
            // //0..
            //    //quad;
            //}
        }
    }
    file.close();
    return;
}