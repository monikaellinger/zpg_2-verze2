#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) {
	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;
}

GLuint ShaderProgram::getProgramId()
{
	return this->shaderProgram;
}

void ShaderProgram::createShaderProgram() {

	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader->getShaderId());
	glAttachShader(this->shaderProgram, fragmentShader->getShaderId());
	glLinkProgram(this->shaderProgram);

	GLint status;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;

		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
}


void ShaderProgram::use()
{
	glUseProgram(this->shaderProgram);
}
