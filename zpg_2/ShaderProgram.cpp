#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	ShaderLoader* shaderLoader = new ShaderLoader();
	this->programID = shaderLoader->loadShader(vertexPath, fragmentPath);

}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath, vector<Light*> lights)
{
	ShaderLoader* shaderLoader = new ShaderLoader();
	this->programID = shaderLoader->loadShader(vertexPath, fragmentPath);
	this->lights = lights;
	this->lightCount = lights.size();
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

void ShaderProgram::use() {

	glUseProgram(this->programID);
	
	if (!lights.empty()) {
		setIntUniform("numberOfLights", this->lightCount);
		for (int i = 0; i < this->lightCount; ++i) {
			sendLight("lights", i, *lights[i]);
		}
	}
	glUniform1i(glGetUniformLocation(this->programID, "textureSampler"), 0);
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

void ShaderProgram::sendLight(const std::string& baseName, int index, const Light& light)
{
	string posName = baseName + "[" + to_string(index) + "].position";
	string diffName = baseName + "[" + to_string(index) + "].diffuse";
	string specName = baseName + "[" + to_string(index) + "].specular";
	string colorName = baseName + "[" + to_string(index) + "].color";
	string dirName = baseName + "[" + to_string(index) + "].direction";
	string cutName = baseName + "[" + to_string(index) + "].cutoff";
	string outName = baseName + "[" + to_string(index) + "].outerCutoff";

	setVec4Uniform(posName.c_str(), light.position);
	setVec4Uniform(diffName.c_str(), light.diffuse);
	setVec4Uniform(specName.c_str(), light.specular);
	setVec4Uniform(colorName.c_str(), light.color);
	setVec3Uniform(dirName.c_str(), light.direction);
	setFloatUniform(cutName.c_str(), light.cutoff);
	setFloatUniform(outName.c_str(), light.outerCutoff);
}


void ShaderProgram::setIntUniform(const char* name, int value)
{
	GLuint id = glGetUniformLocation(this->programID, name);
	if (id == -1) {
		fprintf(stderr, "Error: Uniform variable '%s' not found in shader program.\n", name);
		exit(EXIT_FAILURE);
	}
	glUniform1i(id, value);
}

void ShaderProgram::setFloatUniform(const char* name, float value)
{
	GLuint id = glGetUniformLocation(this->programID, name);
	if (id == -1) {
		fprintf(stderr, "Error: Uniform variable '%s' not found in shader program.\n", name);
		exit(EXIT_FAILURE);
	}
	glUniform1f(id, value);
}


void ShaderProgram::update(Subject* subject)
{
	if (auto camera = dynamic_cast<Camera*>(subject)) {
		setMat4Uniform("viewMatrix", camera->getViewMatrix());
		setMat4Uniform("projectionMatrix", camera->getProjectionMatrix(45.0f, 0.1f, 100.0f));
	}

	if (auto light = dynamic_cast<Light*>(subject)) {
		for (size_t i = 0; i < lights.size(); ++i) {
			if (lights[i] == light) {
				use();
				sendLight("lights", i, *light);
				break;
			}
		}
	}
}
