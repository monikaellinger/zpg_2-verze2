#include "Scene.h"

Scene::Scene(vector<DrawableObject*>& objects)
{
	this->objects = objects;
}

void Scene::addObject(DrawableObject* object)
{
	this->objects.push_back(object);
}

vector<DrawableObject*> Scene::getObjects()
{
	return this->objects;
}

void Scene::render()
{
	//this->shaderProgram->use();
	for (DrawableObject* obj : objects) {
		obj->draw();
	}
}

/*
void Scene::createForest()
{
	Model* tree1 = Model::createTree();
	Transformation* transform_tree1 = new Transformation();
	transform_tree1->scale(0.1f);
	glm::vec3 translation_tree1(0.0f, -4.0f, 0.0f);
	transform_tree1->translate(translation_tree1);

	Model* tree2 = Model::createTree();
	Transformation* transform_tree2 = new Transformation();
	transform_tree2->scale(0.2f);
	glm::vec3 translation_tree2(-2.0f, -5.0f, 0.0f);
	transform_tree2->translate(translation_tree2);

	Model* bush1 = Model::createBush();
	Transformation* transform_bush1 = new Transformation();
	transform_bush1->scale(0.1f);
	glm::vec3 translation_bush1(1.0f, -4.0f, 0.0f);
	transform_bush1->translate(translation_bush1);

	Model* bush2 = Model::createBush();
	Transformation* transform_bush2 = new Transformation();
	transform_bush2->scale(0.5f);
	glm::vec3 translation_bush2(2.0f, -5.0f, 0.0f);
	transform_bush2->translate(translation_bush2);

	DrawableObject* obj1 = new DrawableObject(shader_programs[0], tree1, transform_tree1);
	DrawableObject* obj2 = new DrawableObject(shader_programs[0], tree2, transform_tree2);
	DrawableObject* obj3 = new DrawableObject(shader_programs[1], bush1, transform_bush1);
	DrawableObject* obj4 = new DrawableObject(shader_programs[1], bush2, transform_bush2);
	vector<DrawableObject*> objects = { obj1, obj2, obj3, obj4 };
	for (DrawableObject* obj : objects) {
		obj->draw();
	}
}


*/