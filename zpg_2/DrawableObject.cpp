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
	this->shaderProgram->sendAllLights(camera);
	

	if (texture) {
		this->shaderProgram->setTextureID(texture->getTextureID());
		texture->bind();
	}
	if (this->color != glm::vec4(-1.0f))
	{
		this->shaderProgram->setVec4Uniform("objectColor", this->color);
	}
	
	this->shaderProgram->setCamMatrix(camera->getProjectionMatrix(45.f, 0.1f, 100.f), camera->getViewMatrix());
	this->transformation->useTransformation(this->shaderProgram->getTransformID());

	if (this->model->getDraw() == 1)
	{
		this->model->drawModelArrays();
	}
	else {
		this->model->drawModelElements();
	}

	if (texture) {
		texture->unbind();
	}

	this->shaderProgram->stop();

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

void DrawableObject::setTranslation(glm::vec3 matrix, glm::mat4 mat)
{
	this->transformation->translate(matrix, mat);
}

ShaderProgram* DrawableObject::getShaderProgram() const
{
	return shaderProgram;
}

void DrawableObject::setSpin(float angle, float speed, glm::vec3 axis, float deltaTime)
{
	this->transformation->spin(angle, speed, axis, deltaTime);
}

void DrawableObject::setTexture(Texture* newTexture) {
	this->texture = newTexture;
}

void DrawableObject::updateTranslation(int index, glm::vec3 translation)
{
	this->transformation->updateTranslation(index, translation);
}

void DrawableObject::updateRotation(int index, glm::vec3 axis, float angle)
{
	this->transformation->updateRotation(index, axis, angle);
}

void DrawableObject::setMatrix(glm::mat4 matrix)
{
	this->transformation->setMatrix(matrix);
}

glm::mat4 DrawableObject::getMatrix()
{
	return this->transformation->getMatrix();
}
