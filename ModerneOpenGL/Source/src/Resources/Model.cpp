#include <fstream>
#include <sstream>
#include "Log.h"
#include "Model.h"
#include <algorithm>
Model::Model(std::string nameObjFile)
{
    Load("Assets/Meshes/"+nameObjFile);
}

Model::~Model()
{
    vertices.clear();
    indeces.clear();
}

void Model::UnLoad()
{
    delete this;
}

void Model::Load(std::string nameObjFile)
{
    std::ifstream file;

    file.open(nameObjFile);
    if (!file.is_open())
    {
        DEBUG_LOG("This file doesn't exist (" + nameObjFile + ")");
        return;
    }

    std::string str;
    std::string line;

    std::vector<Vector3D> posObj;
    Vector3D v;

    std::vector<Vector2D> textCoordObj;
    Vector2D vt;

    std::vector<Vector3D> normalObj;
    Vector3D vn;

    std::map<std::string, int> tupleIndex;

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

            posObj.push_back(v);
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
            std::vector<int> indexVertexPolygon;
            while (iss >> str)
            {
                auto it = tupleIndex.find(str);
                if (it == tupleIndex.end())
                {
                    tupleIndex[str] = vertices.size();

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
                    Vector3D currentVertexPosition = posObj[std::stoi(vertexInOrder) - 1];
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


                    indexVertexPolygon.push_back(tupleIndex[str]);
                    vertices.push_back(vertex);
                }
                else
                {
                    indexVertexPolygon.push_back(it->second);
                }
            }

            int nbVertexInPoly = indexVertexPolygon.size();

            indeces.push_back(indexVertexPolygon[0]);
            indeces.push_back(indexVertexPolygon[1]);
            indeces.push_back(indexVertexPolygon[2]);

            if (nbVertexInPoly > 3)
            {
                for (int indexInPoly = 3; indexInPoly < nbVertexInPoly; ++indexInPoly)
                {
                    indeces.push_back(indexVertexPolygon[0]);
                    indeces.push_back(indexVertexPolygon[indexInPoly - 1]);
                    indeces.push_back(indexVertexPolygon[indexInPoly]);
                }
            }
        }
    }

    normalObj.clear();
    textCoordObj.clear();
    posObj.clear();

    file.close();
    return;
}