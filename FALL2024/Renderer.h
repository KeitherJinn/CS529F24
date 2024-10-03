#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameWindow.h"
#include "Vector3.h"
#include "Matrix4.h"

class Renderer {
public:
	Renderer(GameWindow& Window);
	void clear(float r, float g, float b, float a);
	void swapBuffers();
	void drawTriangle(Vector3 v1, Vector3 v2, Vector3 v3, Matrix4 model);
	void UpdateTriangle(Matrix4 model);
private:
	unsigned int VBO, VAO, vertexShader, fragmentShader, shaderProgram, transformLocModel, transformLocProjection, transformLocView;
	void initializeVertexShader();
	void initializeFragmentShader();
	void buildShaderProgram();
	void initialize();
	void setupCallbacks();
	void genBuffers();
	void frameBufferSizeCallback(GLFWwindow* w, int l, int h);
	GameWindow& window;
};