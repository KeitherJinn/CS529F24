#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Matrix4.h"
#include "Vector3.h"
#include "Transform.h"
#include "Shader.h"

class Triangle
{
public:
	Triangle(Transform t, Vector3 v1, Vector3 v2, Vector3 v3, Vector3 c1, Vector3 c2, Vector3 c3, Matrix4 m);
	~Triangle();
	void update();
	void changeModelMatrix(Matrix4 m);
private:
	Transform t;
	Shader shader;
	void genBuffers();
	void draw();
	Vector3 toWorldPos(Vector3 v);
	unsigned int VBO, VAO, transformLocModel, transformLocProjection, transformLocView;
	int vertexColorLocation;
	Matrix4 model;
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 vertex3;
	Vector3 color1;
	Vector3 color2;
	Vector3 color3;
};