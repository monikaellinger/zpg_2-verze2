#include "DrawableObject.h"


DrawableObject::DrawableObject(ShaderProgram* shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->model = 0;
	this->transformation = 0;
}

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, glm::vec4 color)
{
	this->shaderProgram = shaderProgram;
	this->color = color;
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
	if (this->color != glm::vec4(-1.0f))
	{
		this->shaderProgram->setVec4Uniform("objectColor", this->color);
	}
	this->shaderProgram->setCamMatrix(camera->getProjectionMatrix(45.f, 0.1f, 100.f), camera->getViewMatrix());
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



