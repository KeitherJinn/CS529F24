#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameWindow.h"

class Renderer {
public:
	Renderer(GameWindow& Window);
	void clear(float r, float g, float b, float a);
	void swapBuffers();
private:
	void initialize();
	void setupCallbacks();
	void frameBufferSizeCallback(GLFWwindow* w, int l, int h);
	GameWindow& window;
};