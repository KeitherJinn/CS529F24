#include "Renderer.h"
#include "GameWindow.h"
#include "Shader.h"
#include "DrawTriangle.h"
#include <iostream>

int main() {
    try {
        GameWindow window(800, 600, "Window");
        Renderer renderer(window);
        //vertex pos& color of triangle 1
        Vector3 v1 = Vector3(0.2f, -0.2f, 0.0f);
        Vector3 v2 = Vector3(-0.2f, -0.2f, 0.0f);
        Vector3 v3 = Vector3(0.0f, 0.2f, 0.0f);
        Vector3 c1 = Vector3(1.0f, 0.0f, 0.0f);
        Vector3 c2 = Vector3(1.0f, 0.0f, 0.0f);
        Vector3 c3 = Vector3(1.0f, 0.0f, 0.0f);
        //vertex pos& color of triangle 2
        Vector3 v4 = Vector3(1.0f, -0.2f, 0.0f);
        Vector3 v5 = Vector3(1.2f, -0.2f, 0.0f);
        Vector3 v6 = Vector3(1.1f, 0.2f, 0.0f);
        Vector3 c4 = Vector3(0.0f, 0.0f, 1.0f);
        Vector3 c5 = Vector3(0.0f, 0.0f, 1.0f);
        Vector3 c6 = Vector3(0.0f, 0.0f, 1.0f);
        //vertex pos& color of triangle 3
        Vector3 v7 = Vector3(0.5f, -0.2f, 0.0f);
        Vector3 v8 = Vector3(0.7f, -0.2f, 0.0f);
        Vector3 v9 = Vector3(0.6f, 0.2f, 0.0f);
        Vector3 c7 = Vector3(0.0f, 1.0f, 0.0f);
        Vector3 c8 = Vector3(0.0f, 1.0f, 0.0f);
        Vector3 c9 = Vector3(0.0f, 1.0f, 0.0f);
        //modelMatrix
        Matrix4 model = Matrix4();
        DrawTriangle t1 = DrawTriangle(v1, v2, v3, c1, c2, c3, model);
        DrawTriangle t2 = DrawTriangle(v4, v5, v6, c4, c5, c6, model);
        DrawTriangle t3 = DrawTriangle(v7, v8, v9, c7, c8, c9, model);
        while (!window.shouldClose()) {
            window.pollEvents();
            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);
            // Render your 3D scene here
            t1.changeModelMatrix(model.rotationY(1 * glfwGetTime()));
            t2.changeModelMatrix(model.rotationY(4 * glfwGetTime()));
            t3.changeModelMatrix(model.rotationY(2 * glfwGetTime()));
            t1.update();
            t2.update();
            t3.update();



            renderer.swapBuffers();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}