#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string& path) : filePath(path) {
    textureID = SOIL_load_OGL_texture(
        path.c_str(),
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        std::cerr << "Failed to load texture: " << SOIL_last_result() << std::endl;
        exit(EXIT_FAILURE);
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::bind(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

