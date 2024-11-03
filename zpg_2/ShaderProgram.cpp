#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	ShaderLoader* shaderLoader = new ShaderLoader();
	this->programID = shaderLoader->loadShader(vertexPath, fragmentPath);
	this->light = NULL;
}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath, Color* color)
{
	ShaderLoader* shaderLoader = new ShaderLoader();
	this->programID = shaderLoader->loadShader(vertexPath, fragmentPath);
	this->color = color;
}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath, Light* light)
{
	ShaderLoader* shaderLoader = new ShaderLoader();
	this->programID = shaderLoader->loadShader(vertexPath, fragmentPath);
	this->light = light;
}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath, Light* light, Color* color)
{
	ShaderLoader* shaderLoader = new ShaderLoader();
	this->programID = shaderLoader->loadShader(vertexPath, fragmentPath);
	this->light = light;
	this->color = color;
}


void ShaderProgram::setMat4Uniform(const char* name, glm::mat4 value)
{
	GLuint id = glGetUniformLocation(this->programID, name);
	if (id == -1) {
		fprintf(stderr, "Error: Uniform variable '%s' not found in shader program.\n", name);
		exit(EXIT_FAILURE);
	}
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setVec3Uniform(const char* name, glm::vec3 value)
{
	GLuint id = glGetUniformLocation(this->programID, name);
	if (id == -1) {
		fprintf(stderr, "Error: Uniform variable '%s' not found in shader program.\n", name);
		exit(EXIT_FAILURE);
	}
	glUniform3fv(id, 1, glm::value_ptr(value));
}

void ShaderProgram::setVec4Uniform(const char* name, glm::vec4 value)
{
	GLuint id = glGetUniformLocation(this->programID, name);
	if (id == -1) {
		fprintf(stderr, "Error: Uniform variable '%s' not found in shader program.\n", name);
		exit(EXIT_FAILURE);
	}
	glUniform4fv(id, 1, glm::value_ptr(value));
}

void ShaderProgram::use()
{
	glUseProgram(this->programID);
	if (this->light != NULL && this->color == NULL) {
		this->setVec3Uniform("lightPosition", this->light->position);
		this->setVec3Uniform("lightColor", this->light->color);
		this->setVec3Uniform("objectColor", this->light->obj_color);
	}
	if (this->color != NULL && this->light == NULL) {
		this->setVec4Uniform("objectColor", this->color->color);
	}
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


