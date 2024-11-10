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
	this->transformation = 0;
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
		this->shaderProgram->setCamMatrix(camera->getProjectionMatrix(32.f, 4.f / 3.f, 0.1f, 100.f), camera->getViewMatrix());
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

ShaderProgram* DrawableObject::getShaderProgram() const
{
	return shaderProgram;
}

void DrawableObject::setSpin(float angle, float speed, glm::vec3 axis, float deltaTime)
{
	this->transformation->spin(angle, speed, axis, deltaTime);
}



