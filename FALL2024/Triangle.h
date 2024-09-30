#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vector3.h"
#include "GameWindow.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <stdexcept>

class Triangle {
public:
	Triangle(Vector3 v1, Vector3 v2, Vector3 v3);
private:
	void initialize(float vertices[]);
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 vertex3;
};