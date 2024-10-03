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
	static void resizeCallbackWrapper(GLFWwindow* w, int l, int h);
	void shutDown();
	void initialize();
public:
	GameWindow(int l, int h, string n);
	GLFWwindow* getNativeWindow() const;
	void setWindowHints(const function<void()>& hintSetter);
	bool setupGraphicsContext();
	void setResizeCallback(function<void(GLFWwindow*, int, int)>callback);
	bool shouldClose();
	void pollEvents();
	void updateWindow();
	void shutdownWindow();
	void shutdownLibraries();
};