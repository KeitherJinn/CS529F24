#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <functional>
#include <stdexcept>
#include "Matrix4.h"
#include "Vector3.h"

class Shader {
public:
	Shader();
	~Shader();
	unsigned int getshaderProgram();
	void initializeVertexShader();
	void initializeFragmentShader();
	void buildShaderProgram();
	void use();
private:
	unsigned int vertexShader, fragmentShader, shaderProgram;
};



