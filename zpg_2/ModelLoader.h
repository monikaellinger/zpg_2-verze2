#include <string>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
/*
struct Vertex {
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

class ModelLoader {
private:
    GLuint VAO;
    GLuint VBO, IBO;
    int indicesCount;

    void processMesh(aiMesh* mesh);

public:
    ModelLoader(const std::string& filePath);
    ~ModelLoader();

    void bind() const;
    void unbind() const;
    int getIndicesCount() const { return indicesCount; }
};
*/