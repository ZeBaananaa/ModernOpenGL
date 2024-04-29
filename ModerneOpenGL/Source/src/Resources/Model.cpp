#include <fstream>
#include <sstream>
#include "Log.h"
#include "Model.h"

#include <unordered_map>
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

int Model::GetIndexVertexInVertices(Vertex v)
{
    size_t i = 0;
    for (; i < vertices.size(); i++)
    {
        if (v == vertices[i])
            return i;
    }

    return i;
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

    std::vector<Vector3D> verticesPosObj;
    Vector3D v;

    std::vector<Vector2D> textCoordObj;
    Vector2D vt;

    std::vector<Vector3D> normalObj;
    Vector3D vn;

    std::map<std::string,Vertex> indexVertex;

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

            verticesPosObj.push_back(v);
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

                Vector3D currentVertexPosition = verticesPosObj[std::stoi(vertexInOrder) - 1];
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

                auto it = indexVertex.find(str);
                if (it == indexVertex.end())
                {
                    indexVertex[str] = vertex;
                    vertices.push_back(vertex);
                    indexVertexPolygon.push_back(vertices.size() - 1);
                }
                else
                {
                    /*int indexInMap = std::distance(indexVertex.begin(), it) - 1;
                    if (indexInMap < 0)
                        indexInMap = 0;*/

                    indexVertexPolygon.push_back(GetIndexVertexInVertices(vertex));
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
    verticesPosObj.clear();

    file.close();
    return;
}