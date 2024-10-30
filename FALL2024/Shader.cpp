#include "Shader.h"

Shader::Shader() : vertexShader(0), fragmentShader(0), shaderProgram(0) {}

Shader::~Shader() {

}

void Shader::use() {
	glUseProgram(shaderProgram);
}

unsigned int Shader::getshaderProgram() {
	return shaderProgram;
}

void Shader::initializeVertexShader() {
	const char* vertexShaderSource =
		"#version 430 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 color;\n"
		"uniform mat4 ModelMatrix;\n"
		"uniform mat4 ViewMatrix;\n"
		"uniform mat4 ProjectionMatrix;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(aPos, 1.0);\n"
		"	color = aColor;\n"
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

void Shader::initializeFragmentShader() {
	const char* fragmentShaderSource =
		"#version 430 core\n"
		"out vec4 FragColor;\n"
		"in vec3 color;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(color, 1.0);\n"
		"}\0";
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	int success;
	char infoLog[512];
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::buildShaderProgram() {
	initializeVertexShader();
	initializeFragmentShader();
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
