#include "Camera.h"

Camera::Camera(string name, Vector3 t) : Node(name), target(t), viewMatrix(Matrix4()), projectionMatrix(Matrix4()) {
	setTarget(t);
	
}

void Camera::setTarget(Vector3 t) {
	Vector3 upVector(0.0f, 1.0f, 0.0f);
	target = t;
	viewMatrix = Matrix4::lookAt(localTransform.getPosition(), t, upVector);
}

void Camera::setProjectionMatrix(float aspectRatio) {
	projectionMatrix = Matrix4::perspective(45.0f * 3.14159f / 180.0f, aspectRatio, 0.1f, 100.0f);
}

Matrix4 Camera::getProjectionMatrix() const {
	return projectionMatrix;
}

Matrix4 Camera::getViewMatrix() const {
	return viewMatrix;
}