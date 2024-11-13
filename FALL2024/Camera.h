#pragma once
#include "Transform.h"
#include "Node.h"

using namespace std;

class Camera : public Node {
public:
	Camera(string name = "camera", Vector3 t = Vector3(0.0f, 0.0f, 0.0f));

	void setTarget(Vector3 t);
	Matrix4 getViewMatrix() const;
protected:
	Vector3 target;
	Matrix4 viewMatrix;
};