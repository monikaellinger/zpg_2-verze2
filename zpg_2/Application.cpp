#include "Application.h"


Application::Application() : lastX(400), lastY(300), firstMouse(true) {
	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->forest = true;
	this->triangle_s = false;
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
	// triangle
	const char* fragment_shader_triangle_def =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (1.5, 1.0, 0.5, 1.0);"
		"}";	

	// sphere
	const char* fragment_shader_sphere_def =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4(0.65, 0.32, 0.16, 1.0);"
		"}";

	// tree
	const char* vertex_shader_def =
		"#version 330\n"
		"layout(location=0) in vec3 vPos;"
		"layout(location=1) in vec3 vColor;"
		"out vec3 fragColor;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 projectionMatrix;"
		"uniform mat4 viewMatrix;"
		"void main () {"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vPos, 1.0);"
		"     fragColor = vColor;"
		"}";
		
	const char* fragment_shader_tree_def =
		"#version 330\n"
		"in vec3 fragColor;"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (fragColor, 1.0);" 
		"}";

	// triangle
	this->triangle_objects.push_back(
		new DrawableObject(
			new ShaderProgram(
				new Shader(GL_VERTEX_SHADER, vertex_shader_def),
				new Shader(GL_FRAGMENT_SHADER, fragment_shader_triangle_def)
			)
		)
	);

	// tree
	for (int i = 1; i <= 100; i++) {
		this->objects.push_back(
			new DrawableObject(
				new ShaderProgram(
					new Shader(GL_VERTEX_SHADER, vertex_shader_def),
					new Shader(GL_FRAGMENT_SHADER, fragment_shader_tree_def)
				)
			)
		);
	}
	/*
	//sphere
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(
				new Shader(GL_VERTEX_SHADER, vertex_shader_def),
				new Shader(GL_FRAGMENT_SHADER, fragment_shader_sphere_def)
			)
		)
	);
	*/

	// bush
	const char* fragment_shader_bush_def =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);"
		"}";

	this->bush_obj_1 = new DrawableObject(new ShaderProgram(new Shader(GL_VERTEX_SHADER, vertex_shader_def), new Shader(GL_FRAGMENT_SHADER, fragment_shader_bush_def)));
	
	/*
	for (int i = 50; i <= 100; i++) {
		this->objects.push_back(
			new DrawableObject(
				new ShaderProgram(
					new Shader(GL_VERTEX_SHADER, vertex_shader_def),
					new Shader(GL_FRAGMENT_SHADER, fragment_shader_bush_def)
				)
			)
		);
	}
	*/
}
vector<DrawableObject*> Application::createTriangleScene()
{

	Model* triangle_model = Model::createTriangle();
	Transformation* triangle_transform = new Transformation();

	triangle_transform->scale(0.2f);

	this->triangle_objects[0]->addModelTransformation(triangle_model, triangle_transform);
	return this->triangle_objects;
	
}

vector<DrawableObject*> Application::createForest()
{

	for (int i = 0; i < 50; ++i) {
		Model* tree_model = Model::createTree();
		Transformation* transform_tree = new Transformation();

		transform_tree->scale(0.2f);

		glm::vec3 translation_tree((i % 5) * 10.0f, -4.0f, (i / 5) * 10.0f);
		transform_tree->translate(translation_tree);

		objects[i]->addModelTransformation(tree_model, transform_tree);
	}
	

	for (int i = 50; i < 100; ++i) {
		Model* bush_model = Model::createBush();
		Transformation* transform_bush = new Transformation();

		transform_bush->scale(0.2f);

		glm::vec3 translation_bush((i % 5) * 1.f, -4.0f, (i / 5) * 9.0f);
		transform_bush->translate(translation_bush);

		objects[i]->addModelTransformation(bush_model, transform_bush);
	}
	/*

	Model* sphere_model = Model::createBush();
	Transformation* transform_sphere = new Transformation();

	transform_sphere->scale(0.2f);

	glm::vec3 translation_sphere(0.f, 0.f, 0.f);
	transform_sphere->translate(translation_sphere);

	//objects[i]->addModelTransformation(sphere_model, transform_sphere);
	*/
	return this->objects;
	
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
		this->triangle_s = true;
		this->forest = false;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		this->triangle_s = false;
		this->forest = true;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwDestroyWindow(window);
	}
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
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
	printf("cursor_callback \n"); 
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
	Scene scene_forest(forest_objects_create);
	Scene scene_triangle(triangle_objects_create);


	while (!glfwWindowShouldClose(this->window))
	{		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (forest == true) {
			scene_forest.render(this->camera);		
		}
		
		if (triangle_s == true) {
			scene_triangle.render(this->camera);
		}

		glfwPollEvents();
		glfwSwapBuffers(this->window);
	}
	
	glfwTerminate();
	exit(EXIT_SUCCESS);

}
