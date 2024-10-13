#include "DrawableObject.h"


DrawableObject::DrawableObject(ShaderProgram* shaderProgram, Model* model, Transformation* transformation)
{
	this->shaderProgram = shaderProgram;
	this->model = model;
	this->transformation = transformation;
}

void DrawableObject::draw()
{
	this->shaderProgram->use();

	GLuint idModelTransform = glGetUniformLocation(this->shaderProgram->getProgramId(), "modelMatrix");
	glm::mat4 modelMatrix = this->transformation->getMatrix();
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &this->transformation->getMatrix()[0][0]);

	this->model->drawModel();
}
