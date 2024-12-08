#pragma once
#include <GL/glew.h>
#include <string>
#include <stdio.h>
#include <iostream>

#include "SOIL.h"
#include "cube.h"

using namespace std;
class CubeTexture
{
private:
	GLuint textureID;
	GLuint id;
public:
	CubeTexture(GLuint id);
	~CubeTexture();
	void bind();
	void unbind();
};
