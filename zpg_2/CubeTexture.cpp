#include "CubeTexture.h"

CubeTexture::CubeTexture(GLuint id)
{
	this->id = id;

	glActiveTexture(GL_TEXTURE0 + this->id);
	this->textureID = SOIL_load_OGL_cubemap("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (this->textureID == NULL) {
		std::cout << "An error occurred while loading CubeMap." << std::endl;
		exit(EXIT_FAILURE);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

}

CubeTexture::~CubeTexture()
{
	glDeleteTextures(1, &this->textureID);
}

void CubeTexture::bind()
{
	glActiveTexture(GL_TEXTURE0 + this->id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
}

void CubeTexture::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}