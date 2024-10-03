#include "GameWindow.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <functional>

GameWindow::GameWindow(int l, int h, string n) : length(l), height(h), name(n) {
	initialize();
}

GLFWwindow* GameWindow::getNativeWindow() const {
	return window;
}

void GameWindow::setWindowHints(const function<void()>& hintSetter) {
	hintSetter();
}

bool GameWindow::setupGraphicsContext() {
	glfwMakeContextCurrent(window);
	return true;
}

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

void GameWindow::initialize() {
	if (!glfwInit()) {
		cerr << "Failed to initialize GLFW" << endl;
	}
	window = glfwCreateWindow(length, height, name.c_str(), nullptr, nullptr);
}

bool GameWindow::shouldClose() {
	return glfwWindowShouldClose(window);
}

void GameWindow::pollEvents() {
	glfwPollEvents();
}

void GameWindow::updateWindow() {
	glfwSwapBuffers(window);
}

void GameWindow::shutdownWindow() {
	glfwDestroyWindow(window);
}

void GameWindow::shutdownLibraries() {
	glfwTerminate();
}