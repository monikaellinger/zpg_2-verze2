#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) {
	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;
	this->programID = glCreateProgram();

	glAttachShader(this->programID, vertexShader->getShaderId());
	glAttachShader(this->programID, fragmentShader->getShaderId());
	glLinkProgram(this->programID);

	GLint status;
	glGetProgramiv(this->programID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->programID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;

		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
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
	glUseProgram(this->programID);
}


GLuint ShaderProgram::getTransformID()
{
	GLuint modelMatrix = glGetUniformLocation(this->programID, "modelMatrix");
	if (modelMatrix == -1)
	{
		fprintf(stderr, "Error: Uniform variable 'modelMatrix' not found in shader program.\n");
		return -1;
	}
	return modelMatrix;
}

void ShaderProgram::update(const glm::mat4& viewMatrix)
{
	glUseProgram(programID);
	GLuint viewLoc = glGetUniformLocation(programID, "viewMatrix");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
}
