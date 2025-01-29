#pragma once
//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Camera.h"
#include "Material.h"
#include "Texture.h"

#include <SOIL.h>
#include <iostream>

class DrawableObject
{
private:
	ShaderProgram* shaderProgram;
	Model* model;
	Transformation* transformation;
	Camera* camera;
	Material* material;
	glm::vec4 color;
	GLuint textureID;
	Texture* texture;


public:
	DrawableObject(ShaderProgram* shaderProgram);
	DrawableObject(ShaderProgram* shaderProgram, glm::vec4 color);
	DrawableObject(ShaderProgram* shaderProgram, Model* model);
	DrawableObject(ShaderProgram* shaderProgram, Model* model, Transformation* transformation);
	void draw(Camera* camera);
	void addModel(Model* model);
	void addTransformation(Transformation* transformation);
	void setScale(float scale);
	void setTranslation(glm::vec3 matrix);
	void setTranslation(glm::vec3 matrix, glm::mat4 mat);
	void setRotation(float angle, glm::vec3 axis);
	Transformation* getTransformastion() const;
	ShaderProgram* getShaderProgram() const;
	void setSpin(float angle, float speed, glm::vec3 axis, float deltaTime);
	void setMaterial(Material* material);
	void setTexture(Texture* newTexture);
	void updateTranslation(int index, glm::vec3 translation);
	void updateRotation(int index, glm::vec3 axis, float angle);
	void setMatrix(glm::mat4 matrix);
	glm::mat4 getMatrix();
};

