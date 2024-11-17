#include "Application.h"


Application::Application() : lastX(400), lastY(300), firstMouse(true) {
	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->triangle_scene = true;
	this->forest_scene = false;
	this->balls_scene = false;
	this->shaders_example_scene = false;
}


Application::~Application()
{

}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

vector<Light*> Application::createLights()
{
	vector<Light*> light_objects;
	Light* light1 = new Light(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	light_objects.push_back(light1);

	Light* light2 = new Light(glm::vec4(2.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light_objects.push_back(light2);
	return light_objects;
}

vector<DrawableObject*> Application::createTriangleScene()
{
	DrawableObject* tr = new DrawableObject(new ShaderProgram("vertex_short_def.vert", "fragment_triangle_def.frag"), glm::vec4(0.8f, 0.8f, 0.f, 1.f));
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
	vector<Light*> lights = createLights();
	ShaderProgram* shader = new ShaderProgram("vertex_phong.vert", "fragment_phong.frag", lights);

	DrawableObject* ball_obj_1 = new DrawableObject(shader, glm::vec4(0.2f, 1.f, 0.2f, 1.f));
	balls_objects.push_back(ball_obj_1);
	this->camera->attach(ball_obj_1->getShaderProgram());

	DrawableObject* ball_obj_2 = new DrawableObject(shader);
	balls_objects.push_back(ball_obj_2);
	this->camera->attach(ball_obj_2->getShaderProgram());

	DrawableObject* ball_obj_3 = new DrawableObject(shader);
	balls_objects.push_back(ball_obj_3);
	this->camera->attach(ball_obj_3->getShaderProgram());

	DrawableObject* ball_obj_4 = new DrawableObject(shader);
	balls_objects.push_back(ball_obj_4);
	this->camera->attach(ball_obj_4->getShaderProgram());

	// ball 1
	Model* balls_model_1 = Model::createSphere();
	Transformation* transform_balls_1 = new Transformation();
	transform_balls_1->scale(0.5f);
	glm::vec3 translation_balls_1(0.f, 3.f, 0.f);
	transform_balls_1->translate(translation_balls_1);

	ball_obj_1->addModel(balls_model_1);
	ball_obj_1->addTransformation(transform_balls_1);

	// ball 2
	Model* balls_model_2 = Model::createSphere();
	Transformation* transform_balls_2 = new Transformation();
	transform_balls_2->scale(0.5f);
	glm::vec3 translation_balls_2(3.f, 0.f, 0.f);
	transform_balls_2->translate(translation_balls_2);

	ball_obj_2->addModel(balls_model_2);
	ball_obj_2->addTransformation(transform_balls_2);

	// ball 3
	Model* balls_model_3 = Model::createSphere();
	Transformation* transform_balls_3 = new Transformation();
	transform_balls_3->scale(0.5f);
	glm::vec3 translation_balls_3(0.f, -3.f, 0.f);
	transform_balls_3->translate(translation_balls_3);

	ball_obj_3->addModel(balls_model_3);
	ball_obj_3->addTransformation(transform_balls_3);

	// ball 4
	Model* balls_model_4 = Model::createSphere();
	Transformation* transform_balls_4 = new Transformation();
	transform_balls_4->scale(0.5f);
	glm::vec3 translation_balls_4(-3.f, 0.f, 0.f);
	transform_balls_4->translate(translation_balls_4);

	ball_obj_4->addModel(balls_model_4);
	ball_obj_4->addTransformation(transform_balls_4);

	return balls_objects;
}

vector<DrawableObject*> Application::createShadersExampleScene()
{
	vector<DrawableObject*> shaders_example_objects;
	// phong
	DrawableObject* ball_obj = new DrawableObject(new ShaderProgram("vertex_phong.vert", "fragment_phong.frag"));
	shaders_example_objects.push_back(ball_obj);
	this->camera->attach(ball_obj->getShaderProgram());

	Model* ball_model = Model::createSphere();
	Transformation* transform_ball = new Transformation();
	transform_ball->scale(0.5f);
	glm::vec3 translation_ball(3.f, 0.f, 0.f);
	transform_ball->translate(translation_ball);
	ball_obj->addModel(ball_model);
	ball_obj->addTransformation(transform_ball);


	// konst
	DrawableObject* tree_obj = new DrawableObject(new ShaderProgram("vertex_phong.vert", "fragment_phong.frag"));
	shaders_example_objects.push_back(tree_obj);
	this->camera->attach(tree_obj->getShaderProgram());

	Model* tree_model = Model::createTree();
	Transformation* transform_tree = new Transformation();
	transform_tree->scale(0.5f);
	glm::vec3 translation_tree(3.f, 0.f, 0.f);
	transform_tree->translate(translation_tree);
	tree_obj->addModel(tree_model);
	tree_obj->addTransformation(transform_tree);



	// lambert
	DrawableObject* sphere = new DrawableObject(new ShaderProgram("vertex_phong.vert", "fragment_lambert.frag"));
	shaders_example_objects.push_back(sphere);
	this->camera->attach(sphere->getShaderProgram());

	Model* sphere_model = Model::createSphere();
	Transformation* transform_sphere = new Transformation();
	transform_sphere->scale(1.0f);
	glm::vec3 translation_sphere(5.f, 5.f, 0.0f);
	transform_sphere->translate(translation_sphere);
	sphere->addModel(sphere_model);
	sphere->addTransformation(transform_sphere);

	return shaders_example_objects;
}


vector<Light*> Application::createLightsForest()
{
	vector<Light*> light_objects;
	for (int i = 0; i < 10; ++i) {
		// Generování náhodných pozic, zajištìní y > 0
		float x = static_cast<float>(rand() % 101 - 50); // -50 až 50
		float y = static_cast<float>(rand() % 50 + 1);   // 1 až 50 (nad osou y = 0)
		float z = static_cast<float>(rand() % 101 - 50); // -50 až 50

		glm::vec4 position = glm::vec4(x, y, z, 1.0f);
		glm::vec4 diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		// Barva svìtla (mùžete mìnit podle potøeby)
		glm::vec4 color = glm::vec4(
			static_cast<float>(rand() % 100) / 100.0f, // Red (0.0 - 1.0)
			static_cast<float>(rand() % 100) / 100.0f, // Green (0.0 - 1.0)
			static_cast<float>(rand() % 100) / 100.0f, // Blue (0.0 - 1.0)
			1.0f                                       // Alpha
		);

		Light* light = new Light(position, diffuse, specular, color);
		light_objects.push_back(light);
	}
	return light_objects;
}

vector<DrawableObject*> Application::createForest()
{
	vector<DrawableObject*> forest_objects;
	ShaderProgram* shader_tree = new ShaderProgram("vertex_def.vert", "fragment_tree_def.frag", createLightsForest());
	ShaderProgram* shader_plain = new ShaderProgram("vertex_def.vert", "fragment_plain_def.frag");
	ShaderProgram* shader_sphere = new ShaderProgram("vertex_phong.vert", "fragment_lambert.frag");

	for (int i = 1; i <= 100; i++) {
		forest_objects.push_back(new DrawableObject(shader_tree));
		this->camera->attach(forest_objects[i - 1]->getShaderProgram());
	}

	DrawableObject* plain = new DrawableObject(shader_plain, glm::vec4(0.0f, 0.f, 1.f, 1.f));
	forest_objects.push_back(plain);
	this->camera->attach(plain->getShaderProgram());

	DrawableObject* sphere = new DrawableObject(shader_sphere, glm::vec4(0.0f, 0.f, 1.f, 1.f));
	forest_objects.push_back(sphere);
	this->camera->attach(sphere->getShaderProgram());


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

		transform_bush->scale(0.2f);

		glm::vec3 translation_bush((i % 5) * 2.f, -4.0f, (i / 5) * 9.0f);
		transform_bush->translate(translation_bush);

		forest_objects[i]->addModel(bush_model);
		forest_objects[i]->addTransformation(transform_bush);
	}

	Model* plain_model = Model::createPlain();
	Transformation* transform_plain = new Transformation();
	transform_plain->scale(100.0f);
	glm::vec3 translation_plain(0.f, -0.008f, 0.0f);
	transform_plain->translate(translation_plain);

	plain->addModel(plain_model);
	plain->addTransformation(transform_plain);

	Model* sphere_model = Model::createSphere();
	Transformation* transform_sphere = new Transformation();
	transform_sphere->scale(1.0f);
	glm::vec3 translation_sphere(5.f, 8.f, 0.0f);
	transform_sphere->translate(translation_sphere);
	sphere->addModel(sphere_model);
	sphere->addTransformation(transform_sphere);

	return forest_objects;

}

void Application::initialize()
{

	glfwSetErrorCallback(this->error_callback_static);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
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
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = true;
		this->balls_scene = false;
		this->shaders_example_scene = false;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = false;
		this->balls_scene = true;
		this->shaders_example_scene = false;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = false;
		this->balls_scene = false;
		this->shaders_example_scene = true;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwDestroyWindow(window);
	}
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
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

	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
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
	vector<DrawableObject*> forest_objects_create = createForest();
	vector<DrawableObject*> triangle_objects_create = createTriangleScene();
	vector<DrawableObject*> balls_objects_create = createBallsScene();
	Scene scene_balls(balls_objects_create);
	//vector<DrawableObject*> shaders_example_objects_create = createShadersExampleScene();
	Scene scene_forest(forest_objects_create);
	Scene scene_triangle(triangle_objects_create);
	//Scene scene_shaders_example(shaders_example_objects_create);
	

	while (!glfwWindowShouldClose(this->window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (forest_scene == true) {
			scene_forest.render(this->camera);
		}
		
		if (triangle_scene == true) {
			scene_triangle.render(this->camera);
		}
		
		if (balls_scene == true) {
			scene_balls.render(this->camera);
		}
		/*
		if (shaders_example_scene == true) {
			scene_shaders_example.render(this->camera);
			shaders_example_objects_create[1]->setSpin(3.0f, 160.0f, glm::vec3(0.0f, 1.0f, 0.0f), 0.016f);
		}
		*/
		glfwPollEvents();
		glfwSwapBuffers(this->window);
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);

}