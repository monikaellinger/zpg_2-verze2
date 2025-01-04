#include <string>

#include <SOIL.h>
#include <GL/glew.h>
using namespace std;

class Texture {
private:
    GLuint textureID;
    std::string filePath;

public:
    Texture(const string& path);
    ~Texture();

    void bind(GLenum textureUnit = GL_TEXTURE0) const;
    void unbind() const;

    GLuint getID() const { return textureID; }
};

