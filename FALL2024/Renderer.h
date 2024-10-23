#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameWindow.h"
#include "Vector3.h"
#include "Matrix4.h"

class Renderer {
public:
	Renderer(GameWindow& Window);

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void clear(float r, float g, float b, float a);
	void swapBuffers();
private:
	void initialize();
	void setupCallbacks();
	void frameBufferSizeCallback(GLFWwindow* w, int l, int h);
	GameWindow& window;
};