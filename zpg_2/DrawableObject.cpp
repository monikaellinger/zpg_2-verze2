#include "DrawableObject.h"


DrawableObject::DrawableObject(ShaderProgram* shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->model = 0;
	this->transformation = 0;
}

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, Model* model)
{
	this->shaderProgram = shaderProgram;
	this->model = model;
}

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, Model* model, Transformation* transformation)
{
	this->shaderProgram = shaderProgram;
	this->model = model;
	this->transformation = transformation;

}

void DrawableObject::draw(Camera* camera)
{
		this->shaderProgram->use();
		this->shaderProgram->setCamMatrix(camera->getProjectionMatrix(50.f, 4.f / 3.f, 0.1f, 100.f), camera->getViewMatrix());
		this->transformation->useTransformation(this->shaderProgram->getTransformID());
		this->model->drawModel();
}

void DrawableObject::addModel(Model* model)
{
	this->model = model;
}

void DrawableObject::addTransformation(Transformation* transformation)
{
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
