#include "DrawTriangle.h"

DrawTriangle::DrawTriangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 c1, Vector3 c2, Vector3 c3, Matrix4 m) : vertex1(v1), vertex2(v2), vertex3(v3), color1(c1), color2(c2), color3(c3), model(m), shader(Shader()) {
	draw();
	update();
	std::cout << "Triangle drawn" << std::endl;
}

DrawTriangle::~DrawTriangle() {
}

void DrawTriangle::changeModelMatrix(Matrix4 m) {
	model = m;
}

void DrawTriangle::genBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void DrawTriangle::draw() {
	float vertices[] = {
		//positions		//colors
		vertex1.x, vertex1.y, vertex1.z, color1.x, color1.y, color1.z,
		vertex2.x, vertex2.y, vertex2.z, color2.x, color2.y, color2.z,
		vertex3.x, vertex3.y, vertex3.z, color3.x, color3.y, color3.z,
	};
	shader.initializeVertexShader();
	shader.initializeFragmentShader();
	shader.buildShaderProgram();
	genBuffers();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DrawTriangle::update() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	shader.use();
	transformLocModel = glGetUniformLocation(shader.getshaderProgram(), "ModelMatrix");
	transformLocView = glGetUniformLocation(shader.getshaderProgram(), "ViewMatrix");
	transformLocProjection = glGetUniformLocation(shader.getshaderProgram(), "ProjectionMatrix");
	vertexColorLocation = glGetUniformLocation(shader.getshaderProgram(), "color");
	shader.use();
	glUniformMatrix4fv(transformLocModel, 1, GL_FALSE, model.getData());
	glUniformMatrix4fv(transformLocView, 1, GL_FALSE, Matrix4().getData());
	glUniformMatrix4fv(transformLocProjection, 1, GL_FALSE, Matrix4().getData());
	glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}