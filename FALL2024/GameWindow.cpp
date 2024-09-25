#include "GameWindow.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <functional>

void GameWindow::resizeCallbackWrapper(GLFWwindow* w, int l, int h) {
	auto* gameWindow = static_cast<GameWindow*>(glfwGetWindowUserPointer(w));
	if (gameWindow && gameWindow->resizeCallback) {
		gameWindow->resizeCallback(w, l, h);
		cout << "Window size: (" << l << "," << h << ")" << endl;
	}
}

void GameWindow::shutDown() {
	if (window) {
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

void GameWindow::setResizeCallback(function<void(GLFWwindow*, int, int)>callback) {
	resizeCallback = move(callback);
}

bool GameWindow::initializeLibraries() {
	if (!glfwInit()) {
		cerr << "Failed to initialize GLFW" << endl;
		return false;
	}
	return true;
}

bool GameWindow::loadGraphicsAPIFunctions() {
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return false;
	}
	return true;
}

void GameWindow::initialize() {
	if (!glfwInit()) {
		cerr << "Failed to initialize GLFW" << endl;
	}
	window = glfwCreateWindow(length, height, name.c_str(), nullptr, nullptr);
}