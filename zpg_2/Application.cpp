#include "Application.h"


Application::Application() : lastX(400), lastY(300), firstMouse(true) {
	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->triangle_scene = false;
	this->forest_scene = false;
	this->balls_scene = false;
	this->skybox_scene = false;
	this->shaders_example_scene = false;
	this->solar_scene = false;
	this->teren_scene = true;
}


Application::~Application()
{

}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

vector<DrawableObject*> Application::createTriangleScene()
{
	DrawableObject* tr = new DrawableObject(new ShaderProgram("vertex_short_def.vert", "fragment_triangle_def.frag"), glm::vec4(0.0f, 0.0f, 1.f, 1.f));
	vector<DrawableObject*> triangle_objects;
	triangle_objects.push_back(tr);

	Model* triangle_model = Model::createTriangle();
	Transformation* triangle_transform = new Transformation();

	triangle_transform->scale(5.f);
	triangle_objects[0]->addModel(triangle_model);
	return triangle_objects;

}

vector<DrawableObject*> Application::createBallsScene()
{
	vector<DrawableObject*> balls_objects;
	vector<Light*> light_objects;

	// Point Light
	Light* light1 = new Light(
		glm::vec3(0.0f, 0.0f, .0f), // Pozice sv�tla
		glm::vec3(1.0f, .0f, .0f),  // �erven� barva sv�tla
		glm::vec3(0.0f, 0.0f, 0.0f),  // Sm�r (nepou��v� se pro Point Light)
		0.0f,                         // Cutoff (nepou��v� se)
		0.0f,                         // Outer cutoff (nepou��v� se)
		1.0f,                         // Konstantn� �len
		0.09f,                        // Line�rn� �len
		0.032f,                       // Kvadratick� �len
		nullptr                       // Kamera (nen� nutn� pro Point Light)
	);
	// Outer cutoff (not used for point light)
	light1->type = LIGHT_TYPE_POINT;
	light_objects.push_back(light1);

	ShaderProgram* shader = new ShaderProgram("vertex_phong.vert", "test_lights.frag", light_objects);
	for (Light* light : light_objects)
	{
		light->attach(shader);
	}


	DrawableObject* ball_obj_1 = new DrawableObject(shader, glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
	balls_objects.push_back(ball_obj_1);
	this->camera->attach(ball_obj_1->getShaderProgram());

	DrawableObject* ball_obj_2 = new DrawableObject(shader, glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
	balls_objects.push_back(ball_obj_2);
	this->camera->attach(ball_obj_2->getShaderProgram());

	DrawableObject* ball_obj_3 = new DrawableObject(shader, glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
	balls_objects.push_back(ball_obj_3);
	this->camera->attach(ball_obj_3->getShaderProgram());

	DrawableObject* ball_obj_4 = new DrawableObject(shader, glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
	balls_objects.push_back(ball_obj_4);
	this->camera->attach(ball_obj_4->getShaderProgram());

	// ball 1
	Model* balls_model_1 = Model::createSphere();
	Transformation* transform_balls_1 = new Transformation();
	transform_balls_1->scale(0.5f);
	glm::vec3 translation_balls_1(0.f, 2.f, .0f);
	transform_balls_1->translate(translation_balls_1);

	ball_obj_1->addModel(balls_model_1);
	ball_obj_1->addTransformation(transform_balls_1);

	// ball 2
	Model* balls_model_2 = Model::createSphere();
	Transformation* transform_balls_2 = new Transformation();
	transform_balls_2->scale(0.5f);
	glm::vec3 translation_balls_2(2.f, 0.f, .0f);
	transform_balls_2->translate(translation_balls_2);

	ball_obj_2->addModel(balls_model_2);
	ball_obj_2->addTransformation(transform_balls_2);

	// ball 3
	Model* balls_model_3 = Model::createSphere();
	Transformation* transform_balls_3 = new Transformation();
	transform_balls_3->scale(0.5f);
	glm::vec3 translation_balls_3(-2.f, 0.f, .0f);
	transform_balls_3->translate(translation_balls_3);

	ball_obj_3->addModel(balls_model_3);
	ball_obj_3->addTransformation(transform_balls_3);

	// ball 4
	Model* balls_model_4 = Model::createSphere();
	Transformation* transform_balls_4 = new Transformation();
	transform_balls_4->scale(0.5f);
	glm::vec3 translation_balls_4(0.f, -2.f, .0f);
	transform_balls_4->translate(translation_balls_4);

	ball_obj_4->addModel(balls_model_4);
	ball_obj_4->addTransformation(transform_balls_4);

	return balls_objects;
}


vector<DrawableObject*> Application::createShadersExampleScene()
{
	vector<Light*> light_objects;

	Light* light1 = new Light(
		glm::vec3(2.0f, 2.0f, 2.0f), // Pozice sv�tla
		glm::vec3(1.0f, 1.0f, 1.0f),  // �erven� barva sv�tla
		glm::vec3(0.0f, 0.0f, 0.0f),  // Sm�r (nepou��v� se pro Point Light)
		0.0f,                         // Cutoff (nepou��v� se)
		0.0f,                         // Outer cutoff (nepou��v� se)
		1.0f,                         // Konstantn� �len
		0.09f,                        // Line�rn� �len
		0.032f,                       // Kvadratick� �len
		nullptr                       // Kamera (nen� nutn� pro Point Light)
	);

	light1->type = LIGHT_TYPE_POINT;
	light_objects.push_back(light1);

	ShaderProgram* shader = new ShaderProgram("vertex_phong.vert", "test_lights.frag", light_objects);

	for (Light* light : light_objects)
	{
		light->attach(shader);
	}

	vector<DrawableObject*> shaders_example_objects;

	// Phong example - Sphere
	DrawableObject* ball_obj = new DrawableObject(shader, glm::vec4(1.f, 0.f, 1.f, 0.f));
	shaders_example_objects.push_back(ball_obj);
	this->camera->attach(ball_obj->getShaderProgram());


	Model* ball_model = Model::createSphere();
	Transformation* transform_ball = new Transformation();
	transform_ball->scale(0.5f);
	glm::vec3 translation_ball(0.f, 0.f, -20.f);
	transform_ball->translate(translation_ball);
	ball_obj->addModel(ball_model);
	ball_obj->addTransformation(transform_ball);

	// Tree (constant object)
	DrawableObject* tree_obj = new DrawableObject(shader, glm::vec4(0.f, 1.f, 0.f, 0.f));
	shaders_example_objects.push_back(tree_obj);
	this->camera->attach(tree_obj->getShaderProgram());

	Model* tree_model = Model::createTree();
	Transformation* transform_tree = new Transformation();
	transform_tree->scale(0.5f);
	glm::vec3 translation_tree(0.f, 0.f, -20.f);
	transform_tree->translate(translation_tree);
	tree_obj->addModel(tree_model);
	tree_obj->addTransformation(transform_tree);

	return shaders_example_objects;
}

vector<DrawableObject*> Application::createSolarSystemScene()
{
	vector<DrawableObject*> solar_system_objects;
	vector<Light*> lights;
	Texture* sunText = new Texture("2k_sun.png", 1);
	Texture* moonText = new Texture("2k_moon.png", 2);
	Texture* eText = new Texture("2k_earth_daymap.png", 3);

	Light* light1 = new Light(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		0.0f,
		0.0f,
		1.0f,
		0.09f,
		0.032f,
		nullptr
	);

	light1->type = LIGHT_TYPE_POINT;
	lights.push_back(light1);

	//ShaderProgram* shader = new ShaderProgram("vertex_phong.vert", "test_lights.frag", lights);
	//ShaderProgram* shader_const = new ShaderProgram("texture_vertex.vert", "fragment_triangle_def.frag");
	ShaderProgram* shader_texture = new ShaderProgram("texture_vertex.vert", "texture_fragment.frag", lights);

	for (Light* light : lights)
	{
		//light->attach(shader);
		light->attach(shader_texture);
	}


	// Slunce P
	DrawableObject* sun_planet = new DrawableObject(new ShaderProgram("texture_vertex.vert", "constant_texture_frag.frag"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	solar_system_objects.push_back(sun_planet);
	this->camera->attach(sun_planet->getShaderProgram());

	Model* sun_model = Model::createLogin("planet.obj");
	Transformation* transform_login = new Transformation();
	transform_login->scale(1.0f);
	glm::vec3 translation_login(0.f, 0.f, 0.0f);
	transform_login->translate(translation_login);
	sun_planet->addModel(sun_model);
	sun_planet->addTransformation(transform_login);
	sun_planet->setTexture(sunText);

	// Earth P
	DrawableObject* earth_planet = new DrawableObject(shader_texture, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	solar_system_objects.push_back(earth_planet);
	this->camera->attach(earth_planet->getShaderProgram());

	Model* earth_model = Model::createLogin("planet.obj");
	Transformation* earth_transform = new Transformation();
	earth_transform->translate(glm::vec3(6.f, 0.f, 0.f));
	earth_transform->scale(0.5f);
	earth_planet->addModel(earth_model);
	earth_planet->addTransformation(earth_transform);
	earth_planet->setTexture(eText);

	// Moon P
	DrawableObject* moon_planet = new DrawableObject(shader_texture, glm::vec4(1.f, 1.f, 1.0f, 1.0f));
	solar_system_objects.push_back(moon_planet);
	this->camera->attach(moon_planet->getShaderProgram());

	Model* moon_model = Model::createLogin("planet.obj");
	Transformation* moon_transform = new Transformation();
	moon_transform->translate(glm::vec3(3.f, 0.f, 0.f));
	moon_transform->scale(0.2f);
	moon_planet->addModel(moon_model);
	moon_planet->addTransformation(moon_transform);
	moon_planet->setTexture(moonText);


	/*
	// Slunce 
	DrawableObject* sun = new DrawableObject(shader, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	solar_system_objects.push_back(sun);
	this->camera->attach(sun->getShaderProgram());

	Model* central_model = Model::createSphere();
	Transformation* central_transform = new Transformation();
	central_transform->scale(1.0f);
	central_transform->translate(glm::vec3(0.f, 0.f, 0.f));
	sun->addModel(central_model);
	sun->addTransformation(central_transform);

	// Zem�
	DrawableObject* earth = new DrawableObject(shader, glm::vec4(0.f, 1.f, 0.0f, 1.0f));
	solar_system_objects.push_back(earth);
	this->camera->attach(earth->getShaderProgram());

	Model* orbiting_model = Model::createSphere();
	Transformation* orbiting_transform = new Transformation();
	orbiting_transform->scale(0.5f);
	orbiting_transform->translate(glm::vec3(0.f, 0.0f, 0.0f));
	earth->addModel(orbiting_model);
	earth->addTransformation(orbiting_transform);

	// Mars
	DrawableObject* mars = new DrawableObject(shader, glm::vec4(1.f, 1.f, 1.0f, 1.0f));
	solar_system_objects.push_back(mars);
	this->camera->attach(mars->getShaderProgram());

	Model* mars_model = Model::createSphere();
	Transformation* mars_transform = new Transformation();
	mars_transform->scale(0.5f);
	mars_transform->translate(glm::vec3(-5.f, 0.0f, 0.0f));
	mars->addModel(mars_model);
	mars->addTransformation(mars_transform);
	*/
	return solar_system_objects;
}

vector<DrawableObject*> Application::createTeren()
{
	vector<DrawableObject*> teren_objects;
	vector<Light*> light_objects;

	//Texture* tree_text = new Texture("tree.png", 5);
	Texture* teren_text = new Texture("grass.png", 5);

	Light* light1 = new Light(
		glm::vec3(1.0f, 5.0f, 1.0f), // Pozice sv�tla
		glm::vec3(1.0f, 1.0f, 1.0f),  // �erven� barva sv�tla
		glm::vec3(0.0f, 0.0f, 0.0f),  // Sm�r (nepou��v� se pro Point Light)
		0.0f,                         // Cutoff (nepou��v� se)
		0.0f,                         // Outer cutoff (nepou��v� se)
		1.0f,                         // Konstantn� �len
		0.09f,                        // Line�rn� �len
		0.032f,                       // Kvadratick� �len
		nullptr                       // Kamera (nen� nutn� pro Point Light)
	);

	light1->type = LIGHT_TYPE_POINT;
	light_objects.push_back(light1);

	ShaderProgram* shader_texture = new ShaderProgram("texture_vertex.vert", "texture_fragment.frag", light_objects);

	for (Light* light : light_objects)
	{
		light->attach(shader_texture);
	}


	DrawableObject* sun_planet = new DrawableObject(new ShaderProgram("texture_vertex.vert", "constant_texture_frag.frag"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	this->teren_scene_pr->addObject(sun_planet);
	this->camera->attach(sun_planet->getShaderProgram());

	Model* sun_model = Model::createLogin("teren.obj");
	Transformation* transform_login = new Transformation();
	glm::vec3 translation_login(0.f, 0.f, 0.0f);
	transform_login->translate(translation_login);
	transform_login->scale(1.f);
	sun_planet->addModel(sun_model);
	sun_planet->addTransformation(transform_login);
	sun_planet->setTexture(teren_text);


	return teren_scene_pr->getObjects();
}


vector<DrawableObject*> Application::createForest()
{
	vector<DrawableObject*> forest_objects;
	vector<Light*> light_objects;
	Texture* grassTexture = new Texture("grass.png", 4);


	Light* light1 = new Light(
		camera->getPosition(),         // Pozice
		glm::vec3(1.0f, 1.0f, 1.0f),   // Barva
		camera->getFront(),            // Sm�r
		glm::cos(glm::radians(12.5f)), // Cutoff
		glm::cos(glm::radians(17.5f)), // Outer cutoff
		1.0f,                          // Konstantn� �len
		0.09f,                         // Line�rn� �len
		0.032f,                        // Kvadratick� �len
		camera                         // Kamera
	);

	light1->type = LIGHT_TYPE_SPOT;
	light_objects.push_back(light1);

	
	Light* light2 = new Light(
		glm::vec3(1.0f, 5.0f, 1.0f), // Pozice sv�tla
		glm::vec3(1.0f, 1.0f, 1.0f),  // �erven� barva sv�tla
		glm::vec3(0.0f, 0.0f, 0.0f),  // Sm�r (nepou��v� se pro Point Light)
		0.0f,                         // Cutoff (nepou��v� se)
		0.0f,                         // Outer cutoff (nepou��v� se)
		1.0f,                         // Konstantn� �len
		0.09f,                        // Line�rn� �len
		0.032f,                       // Kvadratick� �len
		nullptr                       // Kamera (nen� nutn� pro Point Light)
	);

	light2->type = LIGHT_TYPE_POINT;
	light_objects.push_back(light2);


	Light* light3 = new Light(
		glm::vec3(10.0f, 5.0f, 1.0f), // Pozice sv�tla
		glm::vec3(1.0f, 1.0f, 1.0f),  // �erven� barva sv�tla
		glm::vec3(0.0f, 0.0f, 0.0f),  // Sm�r (nepou��v� se pro Point Light)
		0.0f,                         // Cutoff (nepou��v� se)
		0.0f,                         // Outer cutoff (nepou��v� se)
		1.0f,                         // Konstantn� �len
		0.09f,                        // Line�rn� �len
		0.032f,                       // Kvadratick� �len
		nullptr                       // Kamera (nen� nutn� pro Point Light)
	);

	light3->type = LIGHT_TYPE_POINT;
	light_objects.push_back(light3);

	
	for (int i = 0; i < 10; ++i) {
		float x = static_cast<float>(rand() % 101 - 50); // -50 to 50
		float y = static_cast<float>(rand() % 50 + 1);   // 1 to 50 (above y = 0)
		float z = static_cast<float>(rand() % 50 + 1); // -50 to 50		
	}

	ShaderProgram* shader_phong = new ShaderProgram("vertex_phong.vert", "test_lights.frag", light_objects);
	ShaderProgram* shader_texture= new ShaderProgram("texture_vertex.vert", "texture_fragment.frag", light_objects);

	for (Light* light : light_objects)
	{
		light->attach(shader_phong);
		light->attach(shader_texture);
	}


	for (int i = 1; i <= 100; i++) {
		forest_objects.push_back(new DrawableObject(shader_phong, glm::vec4(0.f, 1.f, 0.f, 0.f)));
		this->camera->attach(forest_objects[i - 1]->getShaderProgram());
	}
	
	DrawableObject* plain = new DrawableObject(shader_texture, glm::vec4(0.f, 0.f, 1.f, 0.f));
	forest_objects.push_back(plain);
	this->camera->attach(plain->getShaderProgram());
	
	DrawableObject* sphere = new DrawableObject(shader_phong, glm::vec4(1.f, 1.f, 0.f, 0.f));
	forest_objects.push_back(sphere);
	this->camera->attach(sphere->getShaderProgram());
	
	DrawableObject* login = new DrawableObject(shader_texture, glm::vec4(1.f, 0.f, 0.f, 1.f));
	forest_objects.push_back(login);
	this->camera->attach(login->getShaderProgram());
	


	for (int i = 0; i < 50; ++i) {
		Model* tree_model = Model::createTree();
		Transformation* transform_tree = new Transformation();
		transform_tree->scale(0.2f);
		glm::vec3 translation_tree((i % 5) * 10.0f, -4.0f, (i / 5) * 10.0f);
		transform_tree->translate(translation_tree);

		forest_objects[i]->addModel(tree_model);
		forest_objects[i]->addTransformation(transform_tree);
	}


	for (int i = 50; i < 100; ++i) {
		Model* bush_model = Model::createBush();
		Transformation* transform_bush = new Transformation();

		transform_bush->scale(2.2f);

		glm::vec3 translation_bush((i % 5) * 2.f, -4.0f, (i / 5) * 9.0f);
		transform_bush->translate(translation_bush);

		forest_objects[i]->addModel(bush_model);
		forest_objects[i]->addTransformation(transform_bush);
	}
	
	Model* plain_model = Model::createPlain();
	Transformation* transform_plain = new Transformation();
	transform_plain->scale(10.0f);
	glm::vec3 translation_plain(0.8f, -0.080f, 0.8f);
	transform_plain->translate(translation_plain);
	plain->addModel(plain_model);
	plain->addTransformation(transform_plain);
	plain->setTexture(grassTexture);
	

	Model* sphere_model = Model::createSphere();
	Transformation* transform_sphere = new Transformation();
	transform_sphere->scale(1.0f);
	glm::vec3 translation_sphere(5.f, 8.f, 0.0f);
	transform_sphere->translate(translation_sphere);
	sphere->addModel(sphere_model);
	sphere->addTransformation(transform_sphere);
	
	
	Model* login_model = Model::createLogin("ell0014.obj");
	Transformation* transform_login = new Transformation();
	transform_login->scale(2.0f);
	glm::vec3 translation_login(1.f, 1.f, 0.0f);
	transform_login->translate(translation_login);
	login->addModel(login_model);
	login->addTransformation(transform_login);
	login->setTexture(grassTexture);
	
	return forest_objects;

}


void Application::initialize()
{

	glfwSetErrorCallback(this->error_callback_static);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(1200, 1000, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowUserPointer(this->window, this);
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	glViewport(0, 0, width, height);
}

float Application::getDeltaTime()
{
	static auto lastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> delta = currentTime - lastTime;
	lastTime = currentTime;

	return delta.count();
}


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		this->camera->moveForward();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		this->camera->moveBackward();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		this->camera->moveLeft();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		this->camera->moveRight();
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		this->triangle_scene = true;
		this->forest_scene = false;
		this->balls_scene = false;
		this->shaders_example_scene = false;
		this->skybox_scene = false;
		this->solar_scene = false;
		this->teren_scene = false;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = true;
		this->balls_scene = false;
		this->shaders_example_scene = false;
		this->solar_scene = false;
		this->teren_scene = false;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = false;
		this->balls_scene = true;
		this->shaders_example_scene = false;
		this->solar_scene = false;
		this->teren_scene = false;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = false;
		this->balls_scene = false;
		this->shaders_example_scene = true;
		this->solar_scene = false;
		this->teren_scene = false;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = false;
		this->balls_scene = false;
		this->shaders_example_scene = false;
		this->solar_scene = false;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = false;
		this->balls_scene = false;
		this->shaders_example_scene = false;
		this->solar_scene = true;
		this->teren_scene = false;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = false;
		this->balls_scene = false;
		this->shaders_example_scene = false;
		this->solar_scene = false;
		this->teren_scene = true;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwDestroyWindow(window);
	}
}

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
	this->camera->setAspect(width / height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);
	this->camera->moveMouse(width, height, x, y);

	//printf("cursor_callback \n"); 
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);
		GLint x = static_cast<GLint>(cursorX);
		GLint y = static_cast<GLint>(cursorY);

		GLint width, height;
		glfwGetFramebufferSize(window, &width, &height);
		GLint newY = height - y;

		// �ten� hloubky a stencil bufferu
		GLuint index = 0;
		GLfloat depth = 1.0f;  // V�choz� hodnota je 1.0 (maxim�ln� hloubka)

		glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

		// Pokud hloubka nen� validn�, ukon��me funkci
		if (depth >= 1.0f) {
			printf("Invalid depth value: %f\n", depth);
			return;
		}

		// Z�sk�n� aktu�ln�ho viewportu
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glm::vec4 viewportVec(viewport[0], viewport[1], viewport[2], viewport[3]);

		// P�evod obrazovkov�ch sou�adnic na sv�tov� sou�adnice
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix(45.0f, 0.1f, 100.0f);

		glm::vec3 screenCoords = glm::vec3(x, newY, depth);
		glm::vec3 worldPos = glm::unProject(screenCoords, view, projection, viewportVec);

		printf("Clicked on object ID %u at world position [%f, %f, %f]\n", index, worldPos.x, worldPos.y, worldPos.z);
		
		vector<DrawableObject*> teren_obj;
		vector<Light*> lights;
		Texture* tree_text = new Texture("tree.png", 6);

		Light* light1 = new Light(
			glm::vec3(1.0f, 5.0f, 1.0f), // Pozice sv�tla
			glm::vec3(1.0f, 1.0f, 1.0f),  // �erven� barva sv�tla
			glm::vec3(0.0f, 0.0f, 0.0f),  // Sm�r (nepou��v� se pro Point Light)
			0.0f,                         // Cutoff (nepou��v� se)
			0.0f,                         // Outer cutoff (nepou��v� se)
			1.0f,                         // Konstantn� �len
			0.09f,                        // Line�rn� �len
			0.032f,                       // Kvadratick� �len
			nullptr                       // Kamera (nen� nutn� pro Point Light)
		);

		light1->type = LIGHT_TYPE_POINT;
		lights.push_back(light1);

		ShaderProgram* shader_texture = new ShaderProgram("texture_vertex.vert", "texture_fragment.frag", lights);

		for (Light* light : lights)
		{
			light->attach(shader_texture);
		}

		DrawableObject* tree = new DrawableObject(shader_texture, glm::vec4(0.3f, 0.8f, 0.3f, 1.f));

		Model* treeModel = Model::createLogin("tree.obj");  // Spr�vn� na�ten� modelu
		if (!treeModel) {
			printf("Failed to load tree model!\n");
			return;
		}

		Transformation* transform_tree = new Transformation();
		transform_tree->translate(worldPos);
		transform_tree->scale(0.5f);
		tree->addModel(treeModel);
		tree->addTransformation(transform_tree);
		//tree->setTexture();

		// P�id�n� objektu do sc�ny
		this->teren_scene_pr->addObject(tree);
		printf("Tree added at [%f, %f, %f]\n", worldPos.x, worldPos.y, worldPos.z);
		printf("Total objects: %lu\n", teren_obj.size());
	}
}

void Application::error_callback_static(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->key_callback(window, key, scancode, action, mods);
}

void Application::window_focus_callback_static(GLFWwindow* window, int focused) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->window_focus_callback(window, focused);
}

void Application::window_iconify_callback_static(GLFWwindow* window, int iconified) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->window_iconify_callback(window, iconified);
}

void Application::window_size_callback_static(GLFWwindow* window, int width, int height) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->window_size_callback(window, width, height);
}

void Application::cursor_callback_static(GLFWwindow* window, double x, double y) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->cursor_callback(window, x, y);
}

void Application::button_callback_static(GLFWwindow* window, int button, int action, int mode) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->button_callback(window, button, action, mode);
}



void Application::run()
{

	glfwSetKeyCallback(window, key_callback_static);
	glfwSetWindowFocusCallback(window, window_focus_callback_static);
	glfwSetWindowIconifyCallback(window, window_iconify_callback_static);
	glfwSetWindowSizeCallback(window, window_size_callback_static);
	glfwSetCursorPosCallback(window, cursor_callback_static);
	glfwSetMouseButtonCallback(window, button_callback_static);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	
	vector<DrawableObject*> triangle_objects_create = createTriangleScene();
	vector<DrawableObject*> balls_objects_create = createBallsScene();
	vector<DrawableObject*> shaders_example_objects_create = createShadersExampleScene();
	vector<DrawableObject*> solar_system_objects_create = createSolarSystemScene();
	vector<DrawableObject*> forest_objects_create = createForest();
	vector<DrawableObject*> teren_obj_create = createTeren();
	
	Scene scene_solar_system(solar_system_objects_create);	
	Scene scene_forest(forest_objects_create);
	Scene scene_triangle(triangle_objects_create);
	Scene scene_shaders_example(shaders_example_objects_create);
	Scene scene_balls(balls_objects_create);
	this->teren_scene_pr = new Scene(teren_obj_create);

	float planetAngle = 0.0f, planetSelfRotation = 0.0f;
	float moonAngle = 0.0f, moonSelfRotation = 0.0f;
	

	while (!glfwWindowShouldClose(this->window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (forest_scene == true) {
			for (int i = 0; i < forest_objects_create.size(); i++)
			{
				forest_objects_create[i]->setMatrix(glm::mat4(1.f));
			}
			scene_forest.render(this->camera);
		}
		
		if (triangle_scene == true) {
			for (int i = 0; i < triangle_objects_create.size(); i++)
			{
				triangle_objects_create[i]->setMatrix(glm::mat4(1.f));
			}
			scene_triangle.render(this->camera);
		}

		if (balls_scene == true) {
			for (int i = 0; i < balls_objects_create.size(); i++)
			{
				balls_objects_create[i]->setMatrix(glm::mat4(1.f));
			}
			scene_balls.render(this->camera);
		}
		
		if (solar_scene == true) {

			scene_solar_system.render(this->camera);
			for (int i = 0; i < solar_system_objects_create.size(); i++)
			{
				solar_system_objects_create[i]->setMatrix(glm::mat4(1.f));
			}
			
			// Animace
			float deltaTime = getDeltaTime();

			// Rotace centr�ln� sf�ry kolem vlastn� osy
			solar_system_objects_create[0]->setSpin(1.0f, 50.0f, glm::vec3(0.0f, 1.0f, 0.0f), deltaTime);
			solar_system_objects_create[1]->setSpin(1.0f, 50.0f, glm::vec3(0.0f, 1.0f, 0.0f), deltaTime);
			solar_system_objects_create[2]->setSpin(1.0f, 50.0f, glm::vec3(0.0f, 1.0f, 0.0f), deltaTime);

			static float earth_angle = 0.0f; // �hel pro rotaci Zem� kolem Slunce
			static float moon_angle = 0.0f;  // �hel pro rotaci M�s�ce kolem Zem�

			float earth_speed = glm::radians(360.0f) / 10.0f;
			float moon_speed = glm::radians(360.0f) / 2.0f;

			earth_angle += earth_speed * deltaTime; // Aktualizace �hlu Zem�
			moon_angle += moon_speed * deltaTime;   // Aktualizace �hlu M�s�ce

			// st�ed rotace zem�
			glm::vec3 earth_center = glm::vec3(0.0f, 0.0f, 0.0f);

			float earth_radius = 5.f; 

			float earth_x = earth_radius * glm::cos(earth_angle);
			float earth_z = earth_radius * glm::sin(earth_angle);

			// P�i�azen� nov� pozice orbituj�c� sf�ry
			glm::vec3 earth_position = earth_center + glm::vec3(earth_x, 0.0f, earth_z);
			solar_system_objects_create[1]->updateTranslation(0, earth_position);

			// moon
			glm::vec3 moon_center = earth_position;

			float moon_radius = 1.0f;

			// V�po�et pozice Marsu na kru�nici
			float moon_x = moon_radius * glm::cos(moon_angle);
			float moon_z = moon_radius * glm::sin(moon_angle);

			glm::vec3 moon_position = moon_center + glm::vec3(moon_x, 0.0f, moon_z);
			solar_system_objects_create[2]->updateTranslation(0, moon_position);
		
		
		}
		
		if (shaders_example_scene == true) {
			for (int i = 0; i < shaders_example_objects_create.size(); i++)
			{
				shaders_example_objects_create[i]->setMatrix(glm::mat4(1.f));
			}
			scene_shaders_example.render(this->camera);
			shaders_example_objects_create[1]->setSpin(3.0f, 160.0f, glm::vec3(0.0f, 1.0f, 0.0f), 0.016f);
		}

		if (teren_scene == true) {
			this->teren_scene_pr->render(this->camera);
		}
		
		glfwPollEvents();
		glfwSwapBuffers(this->window);
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}