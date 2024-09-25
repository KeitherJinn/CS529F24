#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <functional>

using namespace std;

class GameWindow {
private:
	GLFWwindow* window;
	int length;
	int height;
	string name;
	function<void(GLFWwindow*, int, int)> resizeCallback;

	bool initializeLibraries();
	bool loadGraphicsAPIFunctions();
	static void resizeCallbackWrapper(GLFWwindow* w, int l, int h);
	void shutDown();
	void initialize();
public:
	GameWindow(int l, float h, string n) : length(l), height(h),name(n) {
		initialize();
	}

	GLFWwindow* getNativeWindow() const {
		return window;
	}

	void setWindowHints(const function<void()>& hintSetter) {
		hintSetter();
	}

	bool setupGraphicsContext() {
		glfwMakeContextCurrent(window);
		return true;
	}

	void setResizeCallback(function<void(GLFWwindow*, int, int)>callback);

	bool shouldClose() {
		return glfwWindowShouldClose(window);
	}

	void pollEvents() {
		glfwPollEvents();
	}

	void updateWindow() {
		glfwSwapBuffers(window);
	}

	void shutdownWindow() {
		glfwDestroyWindow(window);
	}

	void shutdownLibraries() {
		glfwTerminate();
	}

	
};