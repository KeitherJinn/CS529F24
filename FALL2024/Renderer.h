#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameWindow.h"
#include "Vector3.h"

class Renderer {
public:
	Renderer(GameWindow& Window);
	void clear(float r, float g, float b, float a);
	void swapBuffers();
	unsigned int drawTriangle(Vector3 v1, Vector3 v2, Vector3 v3);
private:
	void initialize();
	void setupCallbacks();
	void frameBufferSizeCallback(GLFWwindow* w, int l, int h);
	unsigned int initializeVertexShader();
	unsigned int initializeFragmentShader();
	unsigned int buildShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
	GameWindow& window;
};