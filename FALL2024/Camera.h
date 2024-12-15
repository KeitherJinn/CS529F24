#pragma once
#include "Transform.h"
#include "Node.h"

using namespace std;

class Camera : public Node {
public:
	Camera(string name = "camera", Vector3 t = Vector3(0.0f, 0.0f, 0.0f));

	void setTarget(Vector3 t);
	void setProjectionMatrix(float left, float right, float top, float bottom, float aspectRatio);
	Matrix4 getViewMatrix() const;
	Matrix4 getProjectionMatrix() const;
protected:
	Vector3 target;
	Vector3 position;
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;
};