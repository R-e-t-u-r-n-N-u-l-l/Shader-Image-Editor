#include "window.h"

using namespace engine;

const char* Window::m_droppedPath = nullptr;

Window::Window(int width, int height, const char* title) {
	m_width		 = width;
	m_height	 = height;
	m_title		 = title;

	m_droppedPath = "";

	if (!init())
		glfwTerminate();
}

Window::~Window() {
	glfwDestroyWindow(m_window);

	glfwTerminate();
}

void resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void file_drop_callback(GLFWwindow* window, int count, const char** paths) {
	Window::handleDroppedFile(paths[0]);
}

bool Window::init() {
	if (!glfwInit()) {
		std::cerr << "Error whilst initializing GLFW window" << std::endl;
		return false;
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

	if (!m_window) {
		std::cerr << "Error whilst creating GLFW window" << std::endl;
		return false;
	}

	glfwShowWindow(m_window);
	glfwMakeContextCurrent(m_window);

	glfwSetFramebufferSizeCallback(m_window, resize_callback);
	glfwSetDropCallback(m_window, file_drop_callback);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Error whilst initializing GLEW" << std::endl;
		return false;
	}

	engine::Input input(m_window);

	return true;
}

void Window::handleDroppedFile(const char* path) {
	m_droppedPath = path;
}

void Window::update() {
	GLenum status = glGetError();
	while (status != GL_NO_ERROR) {
		std::cout << "Error with OpenGL: " << status << std::endl;
		status = glGetError();
	}

	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

bool Window::isOpen() const {
	return !glfwWindowShouldClose(m_window);
}

int Window::getWidth() {
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	return m_width;
}

int Window::getHeight() {
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	return m_height;
}

float Window::getAspectRatio() {
	return (float) getWidth() / (float) getHeight();
}

GLFWwindow* Window::getWindow() const {
	return m_window;
}

void Window::setMinVersion(GLuint major, GLuint minor) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void Window::setWindowSize(int width, int height) {
	glfwSetWindowSize(m_window, width, height);
}

void Window::clearDroppedPath() {
	m_droppedPath = "";
}

const char* engine::Window::getDroppedPath() {
	return m_droppedPath;
}
