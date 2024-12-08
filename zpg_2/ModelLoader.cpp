/*#include "ModelLoader.h"
#include <iostream>
#include <cstring>

ModelLoader::ModelLoader(const std::string& filePath) : VAO(0), VBO(0), IBO(0), indicesCount(0) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_OptimizeMeshes |
        aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

    if (!scene) {
        std::cerr << "Failed to load model: " << filePath << "\nError: " << importer.GetErrorString() << std::endl;
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        processMesh(scene->mMeshes[i]);
    }
}

ModelLoader::~ModelLoader() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

void ModelLoader::processMesh(aiMesh* mesh) {
    std::vector<Vertex> vertices(mesh->mNumVertices);
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        if (mesh->HasPositions()) {
            vertices[i].Position[0] = mesh->mVertices[i].x;
            vertices[i].Position[1] = mesh->mVertices[i].y;
            vertices[i].Position[2] = mesh->mVertices[i].z;
        }

        if (mesh->HasNormals()) {
            vertices[i].Normal[0] = mesh->mNormals[i].x;
            vertices[i].Normal[1] = mesh->mNormals[i].y;
            vertices[i].Normal[2] = mesh->mNormals[i].z;
        }

        if (mesh->HasTextureCoords(0)) {
            vertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
            vertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
        }

        if (mesh->HasTangentsAndBitangents()) {
            vertices[i].Tangent[0] = mesh->mTangents[i].x;
            vertices[i].Tangent[1] = mesh->mTangents[i].y;
            vertices[i].Tangent[2] = mesh->mTangents[i].z;
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    indicesCount = indices.size();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Texture));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));

    glBindVertexArray(0);
}

void ModelLoader::bind() const {
    glBindVertexArray(VAO);
}

void ModelLoader::unbind() const {
    glBindVertexArray(0);
}
*/