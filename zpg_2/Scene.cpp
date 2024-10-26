#include "Scene.h"

Scene::Scene(vector<DrawableObject*>& objects)
{
	this->objects = objects;
}

void Scene::render(Camera* camera)
{
	
	for (DrawableObject* obj : objects) {
		obj->draw(camera);
	}
	
}
