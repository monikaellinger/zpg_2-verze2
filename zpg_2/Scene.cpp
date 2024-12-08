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
	
	for (DrawableObject* obj : objects) {
		obj->draw(camera);
	}
	
}

ShaderProgram* Scene::getShaderProgram()
{
	return shader_program;
}
