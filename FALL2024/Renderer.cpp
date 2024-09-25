#include "Renderer.h"
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <functional>

Renderer::Renderer(GameWindow& w) : window(w) {
	initialize();
	setupCallbacks();
}

void Renderer::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swapBuffers() {
	glfwSwapBuffers(window.getNativeWindow());
}

void Renderer::initialize() {
	window.setWindowHints([]() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		});
	glfwMakeContextCurrent(window.getNativeWindow());
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
	}
}

void Renderer::setupCallbacks() {
	window.setResizeCallback([this](GLFWwindow* w, int l, int h) {
		this->frameBufferSizeCallback(w, l, h);
		});
}

void Renderer::frameBufferSizeCallback(GLFWwindow* w, int l, int h) {
	glViewport(0, 0, l, h);
}