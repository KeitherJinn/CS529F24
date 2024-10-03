#include "Renderer.h"
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <functional>

Renderer::Renderer(GameWindow& w) : window(w) {
	initialize();
	setupCallbacks();
}

void Renderer::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swapBuffers() {
	glfwSwapBuffers(window.getNativeWindow());
}

void Renderer::initialize() {
	window.setWindowHints([]() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		});
	glfwMakeContextCurrent(window.getNativeWindow());
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
	}
}

void Renderer::setupCallbacks() {
	window.setResizeCallback([this](GLFWwindow* w, int l, int h) {
		this->frameBufferSizeCallback(w, l, h);
		});
}

void Renderer::frameBufferSizeCallback(GLFWwindow* w, int l, int h) {
	glViewport(0, 0, l, h);
}

void Renderer::genBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void Renderer::drawTriangle(Vector3 v1, Vector3 v2, Vector3 v3, Matrix4 model) {
	float vertices[] = {
	v1.x, v1.y, v1.z,
	v2.x, v2.y, v2.z,
	v3.x, v3.y, v3.z,
	};
	initializeVertexShader();
	initializeFragmentShader();
	buildShaderProgram();
	genBuffers();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::UpdateTriangle(Matrix4 model) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glUseProgram(shaderProgram);
	transformLocModel = glGetUniformLocation(shaderProgram, "ModelMatrix");
	transformLocView = glGetUniformLocation(shaderProgram, "ViewMatrix");
	transformLocProjection = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
	glUniformMatrix4fv(transformLocModel, 1, GL_FALSE, model.getData());
	glUniformMatrix4fv(transformLocView, 1, GL_FALSE, Matrix4().getData());
	glUniformMatrix4fv(transformLocProjection, 1, GL_FALSE, Matrix4().getData());
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::initializeVertexShader() {
	const char* vertexShaderSource = 
		"#version 430 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 ModelMatrix;\n"
		"uniform mat4 ViewMatrix;\n"
		"uniform mat4 ProjectionMatrix;\n"
		"void main()\n"
		"{\n"
		//"   gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"   gl_Position = ModelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Renderer::initializeFragmentShader() {
	const char* fragmentShaderSource = 
		"#version 430 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
		"}\0";
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	int success;
	char infoLog[512];
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Renderer::buildShaderProgram() {
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
