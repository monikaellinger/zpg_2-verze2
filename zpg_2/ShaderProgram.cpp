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

ShaderProgram::ShaderProgram(const char* vertex, const char* fragment)
{
	ShaderLoader* sl = new ShaderLoader();
	this->programID = sl->loadShader(vertex, fragment);
}




void ShaderProgram::use()
{
	glUseProgram(this->programID);
}

void ShaderProgram::update(Subject* subject)
{
}

GLuint ShaderProgram::getProjectionMatrixID()
{
	GLuint projMat = glGetUniformLocation(this->programID, "projectionMatrix");

	if (projMat == -1)
	{
		//fprintf(stderr, "Error: Uniform variable 'projectionMatrix' not found in shader program.\n");
		return -1;
	}
	return projMat;
}

GLuint ShaderProgram::getViewMatrixID()
{
	GLuint viewMat = glGetUniformLocation(this->programID, "viewMatrix");
	if (viewMat == -1)
	{
		//fprintf(stderr, "Error: Uniform variable 'viewMatrix' not found in shader program.\n");
		return -1;
	}
	return viewMat;
}


GLuint ShaderProgram::getTransformID()
{
	GLuint modelMatrix = glGetUniformLocation(this->programID, "modelMatrix");
	if (modelMatrix == -1)
	{
		//fprintf(stderr, "Error: Uniform variable 'modelMatrix' not found in shader program.\n");
		return -1;
	}
	return modelMatrix;
}


void ShaderProgram::setCamMatrix(glm::mat4 projectionMat, glm::mat4 viewMat)
{
	glUniformMatrix4fv(this->getViewMatrixID(), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(this->getProjectionMatrixID(), 1, GL_FALSE, glm::value_ptr(projectionMat));
}

