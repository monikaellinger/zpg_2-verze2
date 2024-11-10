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
	if (this->light != NULL && this->color != NULL) {
		this->setVec3Uniform("lightPosition", this->light->position);
		this->setVec3Uniform("lightColor", this->light->color);
		this->setVec4Uniform("objectColor", this->color->color);
	}
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

void ShaderProgram::sendLight(const string& baseName, int index, glm::vec4 position, glm::vec4 diffuse, glm::vec4 specular)
{
	string posName = baseName + "[" + to_string(index) + "].position";
	string diffName = baseName + "[" + to_string(index) + "].diffuse";
	string specName = baseName + "[" + to_string(index) + "].specular";

	setVec4Uniform(posName.c_str(), position);
	setVec4Uniform(diffName.c_str(), diffuse);
	setVec4Uniform(specName.c_str(), specular);
}

void ShaderProgram::setNumberOfLights(int count)
{
	setIntUniform("numberOfLights", count);
}

void ShaderProgram::setIntUniform(const char* name, int value)
{
	GLuint id = glGetUniformLocation(this->programID, name);
	if (id == -1) {
		//fprintf(stderr, "Error: Uniform variable '%s' not found in shader program.\n", name);
		exit(EXIT_FAILURE);
	}
	glUniform1i(id, value);

}


void ShaderProgram::update(Subject* subject) 
{
	if (auto camera = dynamic_cast<Camera*>(subject)) {
		use();
		setMat4Uniform("viewMatrix", camera->getViewMatrix());
		setMat4Uniform("projectionMatrix", camera->getProjectionMatrix(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)); 
	}
	/*
	if (auto light = dynamic_cast<Light*>(subject)
	{
		use();
		setVec3Uniform("lightPosition", light->getPosition());
		setVec3Uniform("lightColor", light->getPosition());
	}
	*/
}
