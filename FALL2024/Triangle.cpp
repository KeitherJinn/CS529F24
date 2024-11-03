#include "Triangle.h"

Triangle::Triangle(Transform transform, Vector3 v1, Vector3 v2, Vector3 v3, Vector3 c1, Vector3 c2, Vector3 c3, Matrix4 m) : t(transform), vertex1(v1), vertex2(v2), vertex3(v3), color1(c1), color2(c2), color3(c3), model(m), shader(Shader()) {
	draw();
	update();
	std::cout << "Triangle drawn" << std::endl;
}

Triangle::~Triangle() {
}

void Triangle::changeModelMatrix(Matrix4 m) {
	model = m;
}

Vector3 Triangle::toWorldPos(Vector3 v) {
	v = v + t.getPosition();
	Matrix4 rotate;
	rotate = rotate.rotationXYZ(t.getRotation().x, t.getRotation().y, t.getRotation().z);
	v = rotate * v;
	v.x = v.x * t.getScale().x;
	v.y = v.y * t.getScale().y;
	v.z = v.z * t.getScale().z;
	return v;
}

void Triangle::genBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void Triangle::draw() {
	Vector3 v1 = toWorldPos(vertex1);
	Vector3 v2 = toWorldPos(vertex2);
	Vector3 v3 = toWorldPos(vertex3);
	float vertices[] = {
		//positions		//colors
		v1.x, v1.y, v1.z, color1.x, color1.y, color1.z,
		v2.x, v2.y, v2.z, color2.x, color2.y, color2.z,
		v3.x, v3.y, v3.z, color3.x, color3.y, color3.z,
	};
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

void Triangle::update() {
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