#include "Renderer.h"
#include "GameWindow.h"
#include "Shader.h"
#include "Triangle.h"
#include "Transform.h"
#include <iostream>

int main() {
    try {
        GameWindow window(800, 600, "Window");
        Renderer renderer(window);
        //vertex pos of triangles
        Vector3 v1 = Vector3(0.2f, -0.2f, 0.0f);
        Vector3 v2 = Vector3(-0.2f, -0.2f, 0.0f);
        Vector3 v3 = Vector3(0.0f, 0.2f, 0.0f);
        //transform of triangles
        Transform t1;
        t1.setPosition(Vector3(0.0f, 0.0f, 0.0f));
        Transform t2;
        t2.setPosition(Vector3(1.0f, 0.0f, 0.0f));
        Transform t3;
        t3.setPosition(Vector3(0.5f, 0.0f, 0.0f));
        //vertex color of triangle 1
        Vector3 c1 = Vector3(1.0f, 0.0f, 0.0f);
        Vector3 c2 = Vector3(1.0f, 0.0f, 0.0f);
        Vector3 c3 = Vector3(1.0f, 0.0f, 0.0f);
        //vertex color of triangle 2
        Vector3 c4 = Vector3(0.0f, 0.0f, 1.0f);
        Vector3 c5 = Vector3(0.0f, 0.0f, 1.0f);
        Vector3 c6 = Vector3(0.0f, 0.0f, 1.0f);
        //vertex color of triangle 3
        Vector3 c7 = Vector3(0.0f, 1.0f, 0.0f);
        Vector3 c8 = Vector3(0.0f, 1.0f, 0.0f);
        Vector3 c9 = Vector3(0.0f, 1.0f, 0.0f);
        //modelMatrix
        Matrix4 model = Matrix4();
        Triangle tr1 = Triangle(t1, v1, v2, v3, c1, c2, c3, model);
        Triangle tr2 = Triangle(t2, v1, v2, v3, c4, c5, c6, model);
        Triangle tr3 = Triangle(t3, v1, v2, v3, c7, c8, c9, model);
        while (!window.shouldClose()) {
            window.pollEvents();
            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);
            // Render your 3D scene here
            tr1.changeModelMatrix(model.rotationY(1 * glfwGetTime()));
            tr2.changeModelMatrix(model.rotationY(4 * glfwGetTime()));
            tr3.changeModelMatrix(model.rotationY(2 * glfwGetTime()));

            tr1.update();
            tr2.update();
            tr3.update();

            renderer.swapBuffers();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}