#include "Camera.h"

Camera::Camera(string name, Vector3 t) : Node(name), target(t), viewMatrix(Matrix4()) {
	setTarget(t);
}

void Camera::setTarget(Vector3 t) {
	Vector3 upVector(0.0f, 1.0f, 0.0f);
	target = t;
	viewMatrix = Matrix4::lookAt(localTransform.getPosition(), t, upVector);
}

Matrix4 Camera::getViewMatrix() const {
	return viewMatrix;
}