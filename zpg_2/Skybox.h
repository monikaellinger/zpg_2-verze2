#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "CubeTexture.h"
#include "Observer.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "cube.h"


class Skybox : public Observer
{
private:
	CubeTexture* texture;
	GLuint VAO;
	GLuint VBO;
	bool followCamera = true;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	ShaderProgram* shaderProgram;

public:
	Skybox();
	~Skybox();
	void draw();
	//void setTexture(GLuint texture);

	void draw(Camera* camera);
	// implement all the necessary functions from observer
	ShaderProgram* getShaderProgram() const;

	void update(Subject* subject) override;

};
