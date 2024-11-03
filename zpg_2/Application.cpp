#include "Application.h"


Application::Application() : lastX(400), lastY(300), firstMouse(true) {
	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->triangle_scene = false;
	this->forest_scene = false;
	this->balls = true;
}


Application::~Application()
{

}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


void Application::compileShaders()
{
	/*this->triangle_objects.push_back(
		new DrawableObject(new ShaderProgram("vertex_short_def.vert", "fragment_triangle_def.frag")));

	//this->light_shader = new ShaderProgram("vertex_balls_def.vert", "fragment_balls_def.frag");
	
	// FOREST
	for (int i = 1; i <= 100; i++) {
		this->forest_objects.push_back(
			new DrawableObject(
				new ShaderProgram("vertex_def.vert", "fragment_tree_def.frag")));
	}

	this->plain = new DrawableObject(new ShaderProgram("vertex_def.vert", "fragment_plain_def.frag"));
	this->forest_objects.push_back(plain);

	this->sphere = new DrawableObject(new ShaderProgram("vertex_def.vert", "fragment_sphere_def.frag"));
	this->forest_objects.push_back(sphere);
	*/

}
vector<DrawableObject*> Application::createTriangleScene()
{

	Model* triangle_model = Model::createTriangle();
	Transformation* triangle_transform = new Transformation();

	triangle_transform->scale(5.f);
	this->triangle_objects[0]->addModel(triangle_model);
	return this->triangle_objects;
	
}

vector<DrawableObject*> Application::createBallsScene()
{
	vector<DrawableObject*> objects;
	ShaderProgram* spBalls = new ShaderProgram("vertex_balls_def.vert", "fragment_balls_def.frag");

	//ball 1
	/*Model* ball_model_1 = Model::createSphere();
	Transformation* transform_ball_1 = new Transformation(0.5f, glm::vec3(0.f, 3.f, 0.f), 0.f, glm::vec3(0.f, 0.f, 0.f));
	DrawableObject* ball_1 = new DrawableObject(spBalls, ball_model_1, transform_ball_1);
	objects.push_back(ball_1);

	this->balls_scene = new Scene(objects);
	*/


	
	this->ball_obj_1 = new DrawableObject(new ShaderProgram("vertex_balls_def.vert", "fragment_balls_def.frag"));
	this->balls_objects.push_back(ball_obj_1);

	this->ball_obj_2 = new DrawableObject(new ShaderProgram("vertex_balls_def.vert", "fragment_balls_def.frag"));
	this->balls_objects.push_back(ball_obj_2);

	this->ball_obj_3 = new DrawableObject(new ShaderProgram("vertex_balls_def.vert", "fragment_balls_def.frag"));
	this->balls_objects.push_back(ball_obj_3);

	this->ball_obj_4 = new DrawableObject(new ShaderProgram("vertex_balls_def.vert", "fragment_balls_def.frag"));
	this->balls_objects.push_back(ball_obj_4);

	// ball 1
	Model* balls_model_1 = Model::createSphere();
	Transformation* transform_balls_1 = new Transformation();

	transform_balls_1->scale(0.5f);

	glm::vec3 translation_balls_1(0.f, 3.f, 0.f);
	transform_balls_1->translate(translation_balls_1);

	this->balls_objects[0]->addModel(balls_model_1);
	this->balls_objects[0]->addTransformation(transform_balls_1);
	
	// ball 2
	Model* balls_model_2 = Model::createSphere();
	Transformation* transform_balls_2 = new Transformation();

	transform_balls_2->scale(0.5f);

	glm::vec3 translation_balls_2(3.f, 0.f, 0.f);
	transform_balls_2->translate(translation_balls_2);

	this->balls_objects[1]->addModel(balls_model_2);
	this->balls_objects[1]->addTransformation(transform_balls_2);

	// ball 3
	Model* balls_model_3 = Model::createSphere();
	Transformation* transform_balls_3 = new Transformation();

	transform_balls_3->scale(0.5f);

	glm::vec3 translation_balls_3(0.f, -3.f, 0.f);
	transform_balls_3->translate(translation_balls_3);

	this->balls_objects[2]->addModel(balls_model_3);
	this->balls_objects[2]->addTransformation(transform_balls_3);

	// ball 4
	Model* balls_model_4 = Model::createSphere();
	Transformation* transform_balls_4 = new Transformation();

	transform_balls_4->scale(0.5f);

	glm::vec3 translation_balls_4(-3.f, 0.f, 0.f);
	transform_balls_4->translate(translation_balls_4);

	this->balls_objects[3]->addModel(balls_model_4);
	this->balls_objects[3]->addTransformation(transform_balls_4);

	return this->balls_objects;
}

vector<DrawableObject*> Application::createForest()
{

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
	glm::vec3 translation_plain (0.f, -0.008f, 0.0f);
	transform_plain->translate(translation_plain);
	this->plain->addModel(plain_model);
	this->plain->addTransformation(transform_plain);
	
	Model* sphere_model = Model::createSphere();
	Transformation* transform_sphere = new Transformation();
	transform_sphere->scale(1.0f);
	glm::vec3 translation_sphere (5.f, 8.f, 0.0f);
	transform_sphere->translate(translation_sphere);
	this->sphere->addModel(sphere_model);
	this->sphere->addTransformation(transform_sphere);
	
	return this->forest_objects;
	
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
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
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
		this->balls = false;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = true;
		this->balls = false;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		this->triangle_scene = false;
		this->forest_scene = false;
		this->balls = true;
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
	//vector<DrawableObject*> forest_objects_create = createForest();
	//vector<DrawableObject*> triangle_objects_create = createTriangleScene();
	vector<DrawableObject*> balls_objects_create = createBallsScene();
	//Scene scene_forest(createForest());
	//Scene scene_triangle(triangle_objects_create);
	Scene scene_balls(balls_objects_create);


	while (!glfwWindowShouldClose(this->window))
	{		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		/*if (forest_scene == true) {
			scene_forest.render(this->camera);		
		}
		
		if (triangle_scene == true) {
			scene_triangle.render(this->camera);
		}*/

		if (balls == true) {
			scene_balls.render(this->camera);
		}


		glfwPollEvents();
		glfwSwapBuffers(this->window);
	}
	
	glfwTerminate();
	exit(EXIT_SUCCESS);

}
