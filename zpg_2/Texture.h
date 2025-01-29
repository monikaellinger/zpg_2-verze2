#include <string>

#include <SOIL.h>
#include <GL/glew.h>
using namespace std;

class Texture {
private:
    GLuint textureID;
    GLuint id;
    std::string filePath;

public:
    Texture(const string& path, GLuint id);
    ~Texture();

   // void bind(GLenum textureUnit = GL_TEXTURE0) const;
    void bind() const;
    void unbind() const;
    GLuint getTextureID();

    GLuint getID() const { return textureID; }
};

