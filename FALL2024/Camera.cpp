#include "Camera.h"

Camera::Camera(string name, Vector3 t) : Node(name), target(t), viewMatrix(Matrix4()), projectionMatrix(Matrix4()) {}

void Camera::setTarget(Vector3 t) {
	Vector3 upVector(0.0f, 1.0f, 0.0f);
	target = t;
	viewMatrix = Matrix4::lookAt(localTransform.getPosition(), t, upVector);
}

void Camera::setProjectionMatrix(float left, float right, float top, float bottom, float aspectRatio) {
	projectionMatrix = Matrix4::orthographic(left, right, bottom, top, 0.1f, 1000.0f);
}

Matrix4 Camera::getProjectionMatrix() const {
	return projectionMatrix;
}

Matrix4 Camera::getViewMatrix() const {
	return viewMatrix;
}