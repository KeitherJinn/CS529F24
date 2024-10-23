#pragma once
#include "Transform.h"
#include "Node.h"
class Camera : public Node {
public:
	Camera(std::string name, Vector3 dir) : Node(name), direction(dir) {}
protected:
	Vector3 direction;
};