#include "Scene.h"

Scene::Scene(vector<DrawableObject*> objects, ShaderProgram* shaderProgram)
{
	this->objects = objects;
	this->shaderProgram = shaderProgram;
}

void Scene::render()
{
	this->shaderProgram->use();
	for (DrawableObject* obj : objects) {
		obj->draw();
	}
}

