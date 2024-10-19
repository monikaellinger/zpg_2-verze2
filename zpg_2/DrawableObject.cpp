#include "DrawableObject.h"


DrawableObject::DrawableObject(ShaderProgram* shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->model = 0;
	this->transformation = 0;
}

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, Model* model, Transformation* transformation)
{
	this->shaderProgram = shaderProgram;
	this->model = model;
	this->transformation = transformation;
}

void DrawableObject::draw()
{
	if (this->model != nullptr && this->transformation != nullptr) {
		this->shaderProgram->use();
		this->transformation->useTransformation(this->shaderProgram->getTransformID());
		this->model->drawModel();
	}
}

void DrawableObject::addModelTransformation(Model* model, Transformation* transformation)
{
	this->model = model;
	this->transformation = transformation;
}



void DrawableObject::setScale(float scale)
{
	this->transformation->scale(scale);
}

void DrawableObject::setTranslation(glm::vec3 matrix)
{
	this->transformation->translate(matrix);
}

void DrawableObject::setRotation(float angle, glm::vec3 axis)
{
	this->transformation->rotate(angle, axis);
}
