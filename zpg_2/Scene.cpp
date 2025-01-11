#include "Scene.h"

Scene::Scene(vector<DrawableObject*>& objects)
{
	this->objects = objects;
}

Scene::Scene(vector<Skybox*>& skybox_objects)
{
	this->skybox_objects = skybox_objects;
}

Scene::Scene(vector<DrawableObject*>& objects, ShaderProgram* shader_program)
{
	this->objects = objects;
	this->shader_program = shader_program;
}

void Scene::render(Camera* camera)
{	
	for (size_t i = 0; i < objects.size(); ++i) {
		objects[i]->draw(camera);
	}
}

ShaderProgram* Scene::getShaderProgram()
{
	return shader_program;
}

void Scene::addObject(DrawableObject* obj) {
	objects.push_back(obj);
}
